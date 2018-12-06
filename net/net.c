#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "net.h"

#define MASTER_IP "35.237.247.180"
#define PORT "3333"

static int sk;
static struct sockaddr saddr, caddr;
static socklen_t saddrlen, caddrlen;

int
net_init(void)
{
        int status;
        struct addrinfo hints;
        struct addrinfo *res, *p;

        // build socket
        if ((sk = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
                // TODO print something?
                goto err_socket;
        }

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_DGRAM;

        // get server address
        if ((status = getaddrinfo(MASTER_IP, PORT, &hints, &res)) != 0) {
                // TODO print something?
                goto err_addrinfo;
        }
        saddr = *(res->ai_addr);
        saddrlen = res->ai_addrlen;
        freeaddrinfo(res);

        // get client (my) address
        if ((status = getaddrinfo(NULL, PORT, &hints, &res)) != 0) {
                // TODO print something?
                goto err_addrinfo;
        }
        caddr = *(res->ai_addr);
        caddrlen = res->ai_addrlen;
        freeaddrinfo(res);

        // bind client (my) socket
        if (-1 == (bind(sk, &caddr, caddrlen))) {
                // TODO print something?
                goto err_bind;
        }

        return 0;

err_bind:
err_addrinfo:
err_socket:

        return -1;
}
