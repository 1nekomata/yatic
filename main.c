#include <assert.h>
#include <orca/common.h>
#include <orca/log.h>
#include <stdio.h>
#include <stdlib.h>

#include <orca/discord.h>
#include <string.h>

#include "ban.h"
#include "selfburn.h"

void conn(struct discord *client);
void presence_msg(char *msg1, char *msg2, char *msg3);
void on_ks(struct discord *client, const struct discord_message *msg);
void ks(struct discord *client);

void on_test(struct discord *client, const struct discord_message *msg){
    if (msg->author->bot) { return; }

    struct discord_create_message_params params =  { .content = "Good Morning!" };
    discord_create_message(client, msg->channel_id, &params, NULL);
}


void on_lenny(struct discord *client, const struct discord_message *msg){
    if (msg->author->bot) { return; }

    char *reply = ("( ͡° ͜ʖ ͡°)");

    struct discord_create_message_params params =  { .content = reply };
    discord_create_message(client, msg->channel_id, &params, NULL);
}

void selfinit(struct discord *client, const struct discord_message *msg){
    if (msg->author->bot){ return; }
    log_info("%s#%d just sefburned!", msg->author->username, msg->author->discriminator);

    struct discord_create_message_params params = { .content = "ohh! a selfburn!" };
    discord_create_message(client, msg->channel_id, &params, NULL);
    selfburn(client, msg);
}

void on_help(struct discord *client, const struct discord_message *msg){
    if(msg->author->bot) { return; }

    struct discord_create_message_params params = { .content = "`yatic test` for a Greeting\n`lenny` to lenny\n`yatic help me` shows this\n`i wanna experience the selfburn powered by yatic` is an easteregg (make sure you have an invitation link of this server ;]\n\n`yat!ban` and `yat!unban` to ban and unban respectively\n`yat!kick` to kick\n`yat!kill` to delete *every* message sent by user and mute them" };
    discord_create_message(client, msg->channel_id, &params, NULL);
}

int main(int argc, char *argv[]){
    struct discord *conf;
    if (argv[1] == NULL) {
        conf = discord_config_init("config.json");
    } else {
        conf = discord_config_init(argv[1]);
    }
    assert(NULL != conf && "Unable to initialize Client!");

    presence_msg("yatta~! it works!", "i still hate bugfixing tho ._.", "heavy duty writing");

    conn(conf);

    discord_set_on_command(conf, "yatic test", &on_test);
    discord_set_on_command(conf, "lenny", &on_lenny);
    discord_set_on_command(conf, "yatic help me", &on_help);

    discord_set_on_command(conf, "i want to experience the selfburn powered by yatic", &selfinit);

    ks(conf);

    ban(conf);
    unban(conf);

    discord_run(conf);

    discord_cleanup(conf);
    log_info("Exiting cleanly");

    return 0;
}