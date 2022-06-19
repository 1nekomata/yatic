#include "orca/discord.h"
#include "orca/log.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "presence.h"

void on_ready(struct discord *client) {
    const struct discord_user *bot = discord_get_self(client);

    log_info("Bot Connected Successfully as %s#%s", bot->username, bot->discriminator);
    log_info("activity: %s", activity_msg[0]);
    log_info("activity info: %s", activity_msg[1]);
    log_info("status: %s", activity_msg[2]);
    switch (activity_type){
        case DISCORD_ACTIVITY_GAME:
            log_info("acivity type: game");
            break;
        case DISCORD_ACTIVITY_CUSTOM:
            log_info("acivity type: custom");
            break;
        case DISCORD_ACTIVITY_STREAMING:
            log_info("acivity type: streaming");
            break;
        case DISCORD_ACTIVITY_COMPETING:
            log_info("acivity type: competing");
            break;
        case DISCORD_ACTIVITY_LISTENING:
            log_info("acivity type: listening");
            break;
        default:
            log_error("No activity type found!\nMaybe a problem with the Source Code?\nFalling back to activity type: custom");
            activity_type = DISCORD_ACTIVITY_CUSTOM;
            break;
    }
    discord_set_presence(client, &(struct discord_presence_status){ .activities = (struct discord_activity *[]) { &(struct discord_activity){ .name = activity_msg[0], .type = activity_type, .details = activity_msg[1], }, NULL /*End ac array*/ }, .status = activity_msg[2], .afk = afk, .since = discord_timestamp(client), } );
}

void conn(struct discord *client){
    discord_set_on_ready(client, &on_ready);
}