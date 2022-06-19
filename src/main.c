#include <assert.h>
#include <bits/getopt_core.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

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
    int opt;
    char *floc = "config.json";

    activity_msg[0] = "yat!help";
    activity_msg[1] = "v0.1.0";
    activity_msg[2] = " ";
    afk = false;
    activity_type = DISCORD_ACTIVITY_CUSTOM;

    while((opt = getopt(argc, argv, "c:a:i:s:f:t:")) != -1){
        switch (opt) {
            case 'c':
                floc = optarg;
                break;
            case 'a':
                activity_msg[0] = optarg;
                break;
            case 'i':
                activity_msg[1] = optarg;
                break;
            case 's':
                activity_msg[2] = optarg;
                break;
            case 'f':
                if(strcmp(optarg, "false") == 0){
                    afk = false;
                } else if(strcmp(optarg, "true") == 0){
                    afk = true;
                }
                break;
            case 't':
                for(int i = 0; optarg[i] != 0; i++) {
                    optarg[i] = tolower(optarg[i]);
                }

                if(strcmp(optarg, "game") == 0) {
                    activity_type = DISCORD_ACTIVITY_GAME;
                } else if(strcmp(optarg, "listening") == 0) {
                    activity_type = DISCORD_ACTIVITY_LISTENING;
                } else if(strcmp(optarg, "streaming") == 0) {
                    activity_type = DISCORD_ACTIVITY_STREAMING;
                } else if(strcmp(optarg, "competing") == 0) {
                    activity_type = DISCORD_ACTIVITY_COMPETING;
                } else if(strcmp(optarg, "custom") == 0){
                    activity_type = DISCORD_ACTIVITY_CUSTOM;
                } else {
                    log_error("Wrong activity type specified!\nFalling back to activity type Custom");
                }
                break;
            default:
                break;
        }
    }

    conf = discord_config_init(floc);

    assert(NULL != conf && "Unable to initialize Client!");

    conn(conf);

    msg(conf);

    ban(conf);
    unban(conf);

    discord_run(conf);

    discord_cleanup(conf);
    log_info("Exiting cleanly");

    return 0;
}