#include "net.h"

static int lsk;

int
net_init()
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
net_free()
{
        // TODO close sockets!!!
}

void
net_drain()
{
        // process all messages in buffer
        // switch()
        //      - operations
}
