#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <orca/common.h>
#include <orca/log.h>
#include <orca/discord.h>

void kick(struct discord *client, struct discord_message *msg){
    struct discord_guild_member **members = NULL;
    struct discord_list_guild_members_params gpam = { .limit = 1000, .after = 0 };
    
    ORCAcode code;
    if (!members || ORCA_OK != (code = discord_list_guild_members(client, msg->guild_id, &gpam, &members))){
        log_error("Unable to get Member list!");
        struct discord_create_message_params params = { .content = "Unable to get Member list!"};
        discord_create_message(client, msg->channel_id, &params, NULL);
    }


    char *username = NULL, *designator = NULL, *temp = NULL;
    temp = realloc(temp, strlen(msg->content));
    designator = realloc(designator, 5);

    sscanf(msg->content, "%[^#]#%s", temp, designator);

    username = realloc(username, strlen(temp));
    username = temp;
    free(temp);

    if (!*username || !*designator){
        log_error("No User specified");
        struct discord_create_message_params params = { .content = "No User specified? Try again with <username>#<discriminator>" };
        discord_create_message(client, msg->channel_id, &params, NULL);
    }

    int kuser = 0;
    for (int i = 0; members[i]; i++){
        if (0 == strcmp(members[i]->user->username, username) && 0 == strcmp(members[i]->user->discriminator, designator)){
            kuser = i;
            break;
        }
    }
    
    discord_remove_guild_member(client, msg->guild_id, members[kuser]->user->id);
}