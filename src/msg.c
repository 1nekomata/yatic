#include "msg.h"
#include "moderation/ks.h"

void selfburn(struct discord *client, const struct discord_message *msg){
    discord_remove_guild_member(client, msg->guild_id, msg->author->id);
}

void on_test(struct discord *client, const struct discord_message *msg){
    if (msg->author->bot) { return; }

    struct discord_create_message_params params =  { .content = "Hello There!" };
    discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_sus(struct discord *client, const struct discord_message *msg){
    if (msg->author->bot) { return; }

    struct discord_create_message_params params =  { .content = "sus" };
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

    struct discord_create_message_params params = { .content = "`yatic test` for a Greeting\n`amogus` for sus\n`lenny` to lenny\n`yatic help me` or `yat!help` shows this\n`i wanna experience the selfburn powered by yatic` kicks the user who sent the message (make sure you have an invitation link of this server)\n\n`yat!ban` and `yat!unban` to ban and unban respectively\n`yat!kick` to kick the specified user\n`yat!kill` to delete *every* message sent by user and mute them" };
    discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_tsundere(struct discord *client, const struct discord_message *msg){
    if(msg->author->bot) { return; }

    struct discord_create_message_params params = { .content = "dareka tsundere desuka!? baka!! >///<" };
    discord_create_message(client, msg->channel_id, &params, NULL);
}

void msg(struct discord *client){
    discord_set_on_command(client, "yatic test", &on_test);
    discord_set_on_command(client, "amogus", &on_sus);
    discord_set_on_command(client, "lenny", &on_lenny);
    discord_set_on_command(client, "yatic help me", &on_help);
    discord_set_on_command(client, "yat!help", &on_help);
    discord_set_on_command(client, "i wanna experience the selfburn powered by yatic", &selfinit);
    discord_set_on_command(client, "yat!kill", &on_ks);
    discord_set_on_command(client, "yatic is a tsundere", &on_tsundere);
}