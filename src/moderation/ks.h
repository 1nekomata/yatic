#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <orca/discord.h>
#include <orca/common.h>
#include <orca/log.h>
#include <string.h>

#ifndef KS_H
#define KS_H

void on_ks(struct discord *client, const struct discord_message *msg);

#endif