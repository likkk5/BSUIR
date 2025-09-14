CC = gcc

CFLAGS = -Wall

all: server client

server: server.c
	$(CC) $(CFLAGS) server.c -o s

client: client.c
	$(CC) $(CFLAGS) client.c -o c

clean:
	rm -f s c