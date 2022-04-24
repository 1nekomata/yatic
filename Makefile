.PHONY build:
build:
	gcc src/main.c src/msg.c src/conn.c src/moderation/kick.c src/moderation/ks.c src/moderation/ban.c -o yattmab -O2 -Wall -lpthread -ldiscord -lcurl
