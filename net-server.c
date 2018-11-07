#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "doc-server.h"
#include "net.h"
#include "ops.h"

static int lsk;
static int conn[1024];
static int nconn = 0;
static fd_set rfds;
static int fdmax;
static int next_pid = 0;

static void
recv_opmsg(int sk)
{
        opmsg *msg = malloc(sizeof(opmsg));
        read(sk, msg, sizeof(opmsg));
        fprintf(stderr, "Read opmsg from socket\n");
        doc_server_put_op(msg);
}

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

        fprintf(stderr, "Bound %d to (%d, %s)\n",
                                        lsk,
                                        ntohs(((struct sockaddr_in *)res->ai_addr)->sin_port),
                                        inet_ntoa(((struct sockaddr_in *)res->ai_addr)->sin_addr));

        freeaddrinfo(res);

        listen(lsk, 10);

        // fd_set stuff
        FD_ZERO(&rfds);
        FD_SET(lsk, &rfds);
        fdmax = lsk;

        return 0;
}

void
net_server_free()
{
        int i;

        close(lsk);

        for (i=0; i<nconn; i++)
                close(conn[i]);
}

void
net_server_broadcast(opmsg *msg)
{
        int i;

        for (i=0; i<nconn; i++) {
                if (msg->pid == i) {
                        // send ack
                }
                else {
                        // send op
                }
        }
}

void
net_server_drain()
{
        int i;
        int newfd;
        struct sockaddr_storage addr;
        socklen_t addr_size = sizeof(addr);
        fd_set tmpfds = rfds;

        select(fdmax+1, &tmpfds, NULL, NULL, NULL);

        for (i=0; i<nconn; i++) {
                if (FD_ISSET(conn[i], &tmpfds)) {
                        recv_opmsg(conn[i]);
                }
        }

        if (FD_ISSET(lsk, &tmpfds)) {
                newfd = accept(lsk, (struct sockaddr *)&addr, &addr_size);
                conn[nconn] = newfd;
                nconn++;
                FD_SET(newfd, &rfds);
                if (newfd > fdmax)
                        fdmax = newfd;

                // send PID
                write(newfd, &next_pid, sizeof(int));
                next_pid++;
        }
}
