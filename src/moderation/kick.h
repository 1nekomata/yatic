#include <orca/common.h>
#include <orca/log.h>
#include <orca/discord.h>

#ifndef KICK_H
#define KICK_H

void kick(struct discord *client, const struct discord_message *msg);

#endif