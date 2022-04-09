#ifndef DISCORD_H
#include <orca/discord.h>
#endif
#ifndef COMMON_H
#include <orca/common.h>
#endif
#ifndef LOG_H
#include <orca/log.h>
#endif

void selfburn(struct discord *client, const struct discord_message *msg){
    discord_remove_guild_member(client, msg->guild_id, msg->author->id);
}
