#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <orca/discord.h>
#include <orca/common.h>
#include <orca/log.h>
#include <string.h>


void on_ks(struct discord *client, const struct discord_message *msg){
	//Notify mod/admin who will be KillSwitched
	log_info("KillSwitch used by %s#%s", msg->author->username, msg->author->discriminator);
	char *msgs = NULL;
	msgs = realloc(msgs, strlen("KillSwitch used by  # ") + strlen(msg->author->username) + strlen(msg->author->discriminator) + 1);
	sprintf(msgs, "KillSwitch used by %s#%s", msg->author->username, msg->author->discriminator);

	struct discord_create_message_params params = { .content = msgs };
	discord_create_message(client, msg->channel_id, &params, NULL);

	struct discord_create_guild_role_params paramsrole = { .name = "muted by yatic", .permissions = 0, .mentionable = true };
	discord_create_guild_role(client, msg->guild_id, &paramsrole, NULL);

	ORCAcode code;
	//Get ID of the Member to be KillSwitched
	struct discord_guild_member **members;
    struct discord_list_guild_members_params gpam = { .limit = 1000, .after = 0};
    code = discord_list_guild_members(client, msg->guild_id, &gpam, &members);
	if (code != ORCA_OK || !members){ 
        log_error("Unable to get Member list!");    
        struct discord_create_message_params params = { .content = "Unable to get Member list!" };
        discord_create_message(client, msg->channel_id, &params, NULL);
        return;
    }

    char *temp = NULL;
    temp = realloc(temp, strlen(msg->content));

    char *designator = NULL;
    designator = realloc(designator, 5);

    sscanf(msg->content, "%[^#]#%s", temp, designator);

    char *username = NULL;
    username = realloc(username, strlen(temp) + 1);
    strcpy(username, temp);

    free(temp);

    if (!*username || !*designator){ 
        log_error("Unable to find User!");
        struct discord_create_message_params params = { .content = "Unable to find User! Is the User not in this Server*Guild?" };
        discord_create_message(client, msg->channel_id, &params, NULL);
        return;
    }

    struct discord_user *buser = NULL;
    for (int i = 0; members[i]; ++i){
        if (0 == strcmp(members[i]->user->username, username) && 0 == strcmp(members[i]->user->discriminator, designator)){
            buser = members[i]->user;
            break;
        }
    }

    int len;
    
    if (!buser) {
        len = strlen("User  #  is not in this Server/Guild!") + strlen(username) + strlen(designator) + 1;
        char *unh = NULL;
        unh = realloc(unh, len);

        log_error("%s#%s not in Server/Guild!", username, designator);
        snprintf(unh, len, "User %s#%s is not in this Server/Guild!", username, designator);

        struct discord_create_message_params params = { .content = unh};
        discord_create_message(client, msg->channel_id, &params, NULL);

        free(unh);
        free(username);
        free(designator);

        return;
    }

	//Notify mods/admin that messages have been deleted
	code = discord_delete_messages_by_author_id(client, msg->channel_id, buser->id);
	if(code != ORCA_OK){
		log_error("Unable to delete Messages. Continuing anyways");
		char *msgs = "Unable to delete Messages. Continuing anyways";
		struct discord_create_message_params params = { .content = msgs };
		discord_create_message(client, msg->channel_id, &params, NULL);
	} else {
		log_info("Deleted all messages of user %s#%s", buser->username, buser->discriminator);
	}

	msgs = realloc(msgs, strlen("Deleted all Messages of  # ") + strlen(msg->author->username) + sizeof(msg->author->id) + 1);
	sprintf(msgs, "Deleted all Messages of %s#%lu", msg->author->username, msg->author->id);
	params.content = msgs;
	discord_create_message(client, msg->channel_id, &params, NULL);


	struct discord_role **ret;
    code = discord_get_guild_roles(client, msg->guild_id, &ret);

    if (code != ORCA_OK || !ret){ 
        log_error("Unable to get Role list!");    
        struct discord_create_message_params params = { .content = "Unable to get Role list!" };
        discord_create_message(client, msg->channel_id, &params, NULL);
        return;
    }

    struct discord_role *brole = NULL;
    for (int i = 0; ret[i]; ++i){
        if (0 == strcmp(ret[i]->name, "muted by yatic")){
            brole = ret[i];
            break;
        }
    }

    if (!brole) {
        len = strlen("Role is not in this Server/Guild!") + 1;
        char *unh = NULL;
        unh = realloc(unh, len);

        log_error("Role is not in Server/Guild!");
        snprintf(unh, len, "Role is not in this Server/Guild!");

        struct discord_create_message_params params = { .content = unh};
        discord_create_message(client, msg->channel_id, &params, NULL);

        free(unh);
        free(username);
        free(designator);

        return;
    }
	for(int i = 0; ret[i] != NULL; i++){
		discord_remove_guild_member_role(client, msg->guild_id, buser->id, ret[i]->id);
		if(ret[i] == NULL) { break; }
	}
	
	//Add muted role
	code = discord_add_guild_member_role(client, msg->guild_id, buser->id, brole->id);
	
	//Notify
	if(code == ORCA_OK){
		log_info("User %s#%d has been muted", buser->username, buser->discriminator);
		char *msgs = NULL;
		msgs = realloc(msgs, strlen("User  #  has been Muted") + strlen(buser->username) + sizeof(buser->id) + 1);
		sprintf(msgs, "User %s#%lu has been Muted", buser->username, buser->id);
		struct discord_create_message_params params = { .content = msgs };
		discord_create_message(client, msg->channel_id, &params, NULL);

		msgs = realloc(msgs, strlen("User  #  was KillSwitched") + strlen(msg->author->username) + sizeof(msg->author->id) + 1);
		sprintf(msgs, "User %s#%lu was KillSwitched", msg->author->username, msg->author->id);
		params.content = msgs;
	} else {
		char *msgs = NULL;
		msgs = realloc(msgs, strlen("Unable to Mute Target!") + 1);
		sprintf(msgs, "Unable to Mute Target!");

		struct discord_create_message_params params = { .content = msgs };
		discord_create_message(client, msg->channel_id, &params, NULL);
		log_error("Unable to Mute Target!");

		msgs = realloc(msgs, strlen("Failed to KillSwitch User  #  ") + strlen(msg->author->username) + sizeof(msg->author->id) + 1);
		sprintf(msgs, "Failed to KillSwitch User %s#%lu", buser->username, buser->id);
		discord_create_message(client, msg->channel_id, &params, NULL);
		log_error(msgs);
	}
}