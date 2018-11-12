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

        if (rand()%1000 > 200)
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
        operation op, *newop;

        signal(SIGINT, sigint_handler);
        srand(time(NULL));

        if (ot_client_init() || net_client_init())
                goto cleanup;

        //// "instant user input"
        //while (EOF != scanf("%d,%c,%u", &op.type, &op.c, &op.pos)) {
        //        newop = malloc(sizeof(operation));
        //        memcpy(newop, &op, sizeof(operation));

        //        ot_client_put_user_op(newop);
        //}

        //print_document(stderr);

        //for (i=0; i<NROUNDS*10; i++) {
        i=0;
        while (1) {
                if (NROUNDS > i) {
                        do_input();
                        i++;
                }

                //fprintf(stderr, "Client loop\n");
                net_client_drain();
                ot_client_drain();

                print_document(stderr);

                sleep(1);
        }

cleanup:
        net_client_free();
        ot_client_free();

        return 0;
}
