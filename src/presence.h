#ifndef DISCORD_H
#include <orca/discord.h>
#endif

#ifndef PRESENCE_H
#define PRESENCE_H
extern char *activity_msg[3];
extern enum discord_activity_types activity_type;
extern bool afk;
void conn(struct discord *client);
#endif