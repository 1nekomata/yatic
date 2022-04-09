.PHONY build:
build:
	@gcc main.c conn.c kick.c ks.c -o yatic -O2 -Wall -lpthread -ldiscord -lcurl
.PHONY debug:
debug:
	@gcc main.c conn.c kick.c ks.c -o yatic -O2 -Wall -lpthread -ldiscord -lcurl -g