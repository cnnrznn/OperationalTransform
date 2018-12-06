#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "net.h"

static int sk;
static struct sockaddr addr;
static socklen_t addrlen;

int
net_init(char *port)
{
        int status;
        struct addrinfo hints;
        struct addrinfo *res, *p;

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_DGRAM;

        // get client (my) address
        if ((status = getaddrinfo(NULL, port, &hints, &res)) != 0) {
                // TODO print something?
                goto err_addrinfo;
        }

        addr = *(res->ai_addr);
        addrlen = res->ai_addrlen;

        freeaddrinfo(res);

        // build socket
        if ((sk = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
                // TODO print something?
                goto err_socket;
        }

        // bind client (my) socket
        if (-1 == (bind(sk, &addr, addrlen))) {
                // TODO print something?
                goto err_bind;
        }

        return 0;

err_bind:
err_socket:
err_addrinfo:

        return -1;
}

void
net_fini(void)
{
        if (sk >= 0)
                close(sk);
}
