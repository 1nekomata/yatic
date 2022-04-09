#ifndef COMMON_H
#include <orca/common.h>
#endif
#ifndef DISCORD_H
#include <orca/discord.h>
#endif
#ifndef LOG_H
#include <orca/log.h>
#endif
#ifndef STDIO_H
#include <stdio.h>
#endif
#ifndef STDLIB_H
#include <stdlib.h>
#endif
#ifndef STRING_H
#include <string.h>
#endif
#ifndef ASSERT_H
#include <assert.h>
#endif

void on_guild_ban_add(struct discord *client, u64_snowflake_t guild_id, const struct discord_user *user){
    struct discord_channel general = { 0 };

    if (discord_get_channel_at_pos(client, guild_id, DISCORD_CHANNEL_GUILD_TEXT, 0, &general)){
        log_error("Unable to fetch Channel at 0");
        return;
    }
    char *text = NULL;
    text = realloc(text, strlen("User ` ` got banned.") + strlen(user->username));
    snprintf(text, strlen("User ` ` got banned.") + strlen(user->username), "User `%s` got banned.", user->username);

    struct discord_create_message_params params = { .content = text };
    discord_create_message(client, general.id, &params, NULL);

    discord_channel_cleanup(&general);
    free(text);
}

void on_ban(struct discord *client, const struct discord_message *msg){
    struct discord_guild_member **members;
    ORCAcode code;
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

    char *reason = NULL;
    len = strlen(msg->author->username) + strlen(msg->author->discriminator) + strlen("You have been banned by  # ");
    reason = realloc(reason, len);
    snprintf(reason, len, "You have been banned by %s#%s", msg->author->username, msg->author->discriminator);

    struct discord_create_guild_ban_params bpam = { .delete_message_days = 1, .reason = reason };
    discord_create_guild_ban(client, msg->guild_id, buser->id, &bpam);

    discord_guild_member_list_free(members);

    free(reason);
    free(username);
    free(designator);
}

void ban(struct discord *client){
    discord_set_on_guild_ban_add(client, &on_guild_ban_add);
    discord_set_on_command(client, "yat!ban", &on_ban);
}

//unban

void on_guild_ban_remove(struct discord *client, u64_snowflake_t guild_id, const struct discord_user *user){
    struct discord_channel general = { 0 };
    if (discord_get_channel_at_pos(client, guild_id, DISCORD_CHANNEL_GUILD_TEXT, 0, &general)){
        log_error("Unable to get Postion 0 of Channel");
        return;
    }

    char *text = NULL;
    text = realloc(text, strlen("User ` ` got unbanned.") + strlen(user->username));
    snprintf(text, strlen("User ` ` got unbanned.") + strlen(user->username), "User `%s` got unbanned.", user->username);

    struct discord_create_message_params params = { .content = text };
    discord_create_message(client, general.id, &params, NULL);

    discord_channel_cleanup(&general);
    free(text);
}

void on_unban(struct discord *client, const struct discord_message *msg){
    struct discord_ban **bans = NULL;
    ORCAcode code = discord_get_guild_bans(client, msg->guild_id, &bans);
    if (code != ORCA_OK || !bans){
        log_error("No Bans found on this Server/Guild!");
        int len = strlen("No Bans found on this Server/Guild!") + 1;
        char *unh = NULL;
        unh = realloc(unh, len);

        snprintf(unh, len, "No Bans found on this Server/Guild!");

        struct discord_create_message_params params = { .content = unh};
        discord_create_message(client, msg->channel_id, &params, NULL);

        free(unh);
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
    for (int i = 0; bans[i]; ++i){
        if(0 == strcmp(bans[i]->user->username, username) && strcmp(bans[i]->user->discriminator, designator)){
            buser = bans[i]->user;
            return;
        }
    }

    int len;

    if(!buser){
        len = strlen("User  #  was not banned in this Server/Guild!") + strlen(username) + strlen(designator) + 1;
        char *unh = NULL;
        unh = realloc(unh, len);

        log_error("User %s#%s was not banned in this Server/Guild!", username, designator);
        snprintf(unh, len, "User %s#%s was not banned in this Server/Guild!", username, designator);

        struct discord_create_message_params params = { .content = unh};
        discord_create_message(client, msg->channel_id, &params, NULL);

        free(unh);
        free(username);
        free(designator);

        return;
    }
    discord_remove_guild_ban(client, msg->guild_id, buser->id);

    free(username);
    free(designator);

    discord_ban_list_free(bans);
}

void unban(struct discord *client){
    discord_set_on_guild_ban_remove(client, &on_guild_ban_remove);
    discord_set_on_command(client, "yat!unban", &on_unban);
}
