src=$(wildcard *.c)
obj=$(src:.c=.o)

all: server client

server: $(obj)
	gcc mains/server.c -o $@ $^ -I./

client: $(obj)
	gcc mains/client.c -o $@ $^ -I./

.PHONY: clean
clean:
	rm -f $(obj) server client
