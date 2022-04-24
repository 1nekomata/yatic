#include <orca/discord.h>

#ifndef MSG_H
#define MSG_H
void selfburn(struct discord *client, const struct discord_message *msg);
void on_test(struct discord *client, const struct discord_message *msg);
void on_sus(struct discord *client, const struct discord_message *msg);
void on_lenny(struct discord *client, const struct discord_message *msg);
void selfinit(struct discord *client, const struct discord_message *msg);
void on_help(struct discord *client, const struct discord_message *msg);
void msg(struct discord *client);
#endif