#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "net.h"

static int lsk;
static int conn[1024];
static int nconn = 0;

int
net_server_init()
{
        struct addrinfo hints, *res;

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        getaddrinfo(NULL, PORT, &hints, &res);

        if ((lsk = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
                perror("Failed to create socket");
                return -1;
        }

        if (bind(lsk, res->ai_addr, res->ai_addrlen)) {
                perror("Failed to bind socket");
                return -1;
        }

        freeaddrinfo(res);

        listen(lsk, 10);

        return 0;
}

void
net_server_free()
{
        int i;

        // TODO close sockets!!!
        close(lsk);

        for (i=0; i<nconn; i++)
                close(conn[i]);
}

void
net_server_drain()
{
        // process all messages in buffer
        // switch()
        //      - operations
        //      - new connections
}
