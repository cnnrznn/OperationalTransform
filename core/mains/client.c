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

#define NROUNDS 100

static int i;
static char cont = 1;

static void
do_input()
{
        operation *op;

        if (rand()%1000 > 900)
                return;

        op = malloc(sizeof(operation));
        op->type = (rand() % 2) + 1;
        op->c = (rand() % 26) + 97; // a through z
        op->pos = rand() % DOCSIZE;

        ot_client_put_user_op(op);
}

static void
sigint_handler(int sig)
{
        cont = 0;
}

int main(int argc, char **argv)
{
        char *ip, *port;

        signal(SIGINT, sigint_handler);
        srand(time(NULL));

        ip = argv[1];
        port = argv[2];

        if (ot_client_init() || net_client_init(ip, port))
                goto cleanup;

        while (1) {
                net_client_drain();
                ot_client_drain();
        }

cleanup:
        net_client_free();
        ot_client_free();

        return 0;
}
