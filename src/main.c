#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <orca/discord.h>
#include <orca/common.h>
#include <orca/log.h>

#include "moderation/ban.h"
#include "moderation/kick.h"
#include "moderation/ks.h"
#include "presence.h"
#include "msg.h"

char *activity_msg[3];
enum discord_activity_types activity_type;
bool afk;

int main(int argc, char *argv[]){
    struct discord *conf;
    if (argv[1] == NULL) {
        conf = discord_config_init("config.json");
    } else {
        conf = discord_config_init(argv[1]);
    }
    assert(NULL != conf && "Unable to initialize Client!");

    activity_msg[0] = "yat!help ";
    activity_msg[1] = " v0.1.0";
    activity_msg[2] = "";
    afk = false;
    activity_type = DISCORD_ACTIVITY_GAME;

    conn(conf);

    msg(conf);

    ban(conf);
    unban(conf);

    discord_run(conf);

    discord_cleanup(conf);
    log_info("Exiting cleanly");

    return 0;
}