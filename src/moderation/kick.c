#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kick.h"

void kick(struct discord *client, const struct discord_message *msg){
    struct discord_guild_member **members = NULL;
    struct discord_list_guild_members_params gpam = { .limit = 1000, .after = 0 };
    
    ORCAcode code;
    code = discord_list_guild_members(client, msg->guild_id, &gpam, &members);
    if (!members || ORCA_OK != code){
        log_error("Unable to get Member list!");
        struct discord_create_message_params params = { .content = "Unable to get Member list!"};
        discord_create_message(client, msg->channel_id, &params, NULL);
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
   
    discord_remove_guild_member(client, msg->guild_id, buser->id);
}