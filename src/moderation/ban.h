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

void on_guild_ban_add(struct discord *client, u64_snowflake_t guild_id, const struct discord_user *user);
void on_ban(struct discord *client, const struct discord_message *msg);
void ban(struct discord *client);
void on_guild_ban_remove(struct discord *client, u64_snowflake_t guild_id, const struct discord_user *user);
void on_unban(struct discord *client, const struct discord_message *msg);
void unban(struct discord *client);