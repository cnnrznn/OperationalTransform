#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "ot-client.h"
#include "ops.h"
#include "net-client.h"
#include "queue.h"

static char cont = 1;

static void
sigint_handler(int sig)
{
        cont = 0;
}

int main(int argc, char **argv)
{
        operation op, *newop;

        signal(SIGINT, sigint_handler);

        ot_client_init();
        net_client_init();

        // "instant user input"
        while (EOF != scanf("%d,%c,%u", &op.type, &op.c, &op.pos)) {
                newop = malloc(sizeof(operation));
                memcpy(newop, &op, sizeof(operation));

                ot_client_put_user_op(newop);
        }

        print_document(stderr);

        while (1) {
                fprintf(stderr, "Client loop\n");
                net_client_drain();
                ot_client_drain();

                print_document(stderr);
                sleep(1);
        }

        print_document(stdout);

        net_client_free();
        ot_client_free();

        return 0;
}
