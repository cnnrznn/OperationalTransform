#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "ot-client.h"
#include "net.h"
#include "net-client.h"
#include "ops.h"

static int sk;
char net_client_inflight = 0;
int pid;

int
net_client_init(char *ip, char *port)
{
        struct addrinfo hints, *res;
        size_t size;

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        getaddrinfo(ip, port, &hints, &res);

        if ((sk = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
                perror("Failed to create socket");
                return -1;
        }

        freeaddrinfo(res);

        if (connect(sk, res->ai_addr, res->ai_addrlen)) {
                perror("Failed to connect\n");
                return -1;
        }

        // receive PID
        read(sk, &pid, sizeof(int));
        //fprintf(stderr, "PID: %d\n", pid);

        // receive current document, revision
        read(sk, &size, sizeof(size_t));
        op_init(size);
        read(sk, document, size);
        read(sk, &revision, sizeof(uint32_t));

        return 0;
}

void
net_client_free()
{
        int i;

        close(sk);
}

void
net_client_send(operation *op)
{
        message msg;

        msg.pid = pid;
        msg.rev = revision;
        msg.op = *op;

        write(sk, &msg, sizeof(message));
}

void
net_client_drain()
{
        struct pollfd *fds;
        operation *op;
        message msg;
        ssize_t size;

        // TODO error-check lots of things

        fds = malloc(2 * sizeof(struct pollfd));
        fds[0].fd = 0;
        fds[0].events = POLLIN;
        fds[1].fd = sk;
        fds[1].events = POLLIN;

        poll(fds, 2, -1);
        if (fds[0].revents & POLLIN) {
                op = malloc(sizeof(operation));
                scanf("%d,%c,%u", &op->type, &op->c, &op->pos);

                ot_client_put_user_op(op);
        }
        if (fds[1].revents & POLLIN) {
                if (sizeof(message) != (size = recv(sk, &msg, sizeof(message), MSG_DONTWAIT))) {
                        fprintf(stderr, "BAD PACKET SIZE: %ld\n", size);
                        exit(1);
                }

                revision = msg.rev;

                ot_client_put_serv_msg(&msg);
        }
}
