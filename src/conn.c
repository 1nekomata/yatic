#include "orca/discord.h"
#include "orca/log.h"

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "presence.h"

extern char *activity_msg[3];
extern enum discord_activity_types activity_type;
extern bool afk;

void on_ready(struct discord *client) {
    const struct discord_user *bot = discord_get_self(client);

    log_info("Bot Connected Successfully as %s#%s", bot->username, bot->discriminator);
    log_info("activity: %s", activity_msg[0]);
    log_info("activity info: %s", activity_msg[1]);
    log_info("status: %s", activity_msg[2]);
    discord_set_presence(client, &(struct discord_presence_status){ .activities = (struct discord_activity *[]) { &(struct discord_activity){ .name = activity_msg[0], .type = activity_type, .details = activity_msg[1], }, NULL /*End ac array*/ }, .status = activity_msg[2], .afk = afk, .since = discord_timestamp(client), } );
}

void conn(struct discord *client){
    discord_set_on_ready(client, &on_ready);
}