#	TODO:
#		Add Clang support
#		Add Install option

CC = gcc
CFLAGS += -o yattmab -L./orca/lib -I./orca/include -O2 -Wall -lpthread -ldiscord -lcurl
CSOURCE = src/main.c src/msg.c src/conn.c src/moderation/kick.c src/moderation/ks.c src/moderation/ban.c

.PHONY update:
	@git fetch origin
	@git pull
	@git submodule update && git submodule sync
	@${MAKE} -C orca/orca
	@${MAKE} install -C orca/orca PREFIX=${PWD}/orca

build:
	${CC} ${CSOURCE} ${CFLAGS}

.PHONY clean:
clean:
	rm yattmab