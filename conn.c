#include <orca/discord.h>
#include <orca/log.h>

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "presence.h"

void presence_msg(char *msg1, char *msg2, char *msg3) {
    activity_msg[0] = msg1;
    activity_msg[1] = msg2;
    activity_msg[2] = msg3;
}

void on_ready(struct discord *client) {
    const struct discord_user *bot = discord_get_self(client);

    log_info("Bot Connected Successfully as %s#%s", bot->username, bot->discriminator);
    discord_set_presence(client, &(struct discord_presence_status){ .activities = (struct discord_activity *[]) { &(struct discord_activity){ .name = activity_msg[0], .type = activity_type, .details = activity_msg[1], }, NULL /*End ac array*/ }, .status = activity_msg[2], .afk = afk, .since = discord_timestamp(client), } );
}

void conn(struct discord *client){
    discord_set_on_ready(client, &on_ready);
}