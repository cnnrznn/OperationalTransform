#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "doc-client.h"
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
        op o, *newop;

        //signal(SIGINT, sigint_handler);

        doc_client_init();
        net_client_init();

        while (1) {
                fprintf(stderr, "Client loop\n");
                if (EOF != scanf("%d,%c,%u", &o.type, &o.c, &o.pos)) {
                        newop = malloc(sizeof(op));
                        memcpy(newop, &o, sizeof(op));

                        doc_client_put_user_op(newop);
                }
                net_client_drain();
                doc_client_drain();

                print_document(stdout);
                sleep(2);
        }

        print_document(stdout);

        net_client_free();
        doc_client_free();

        return 0;
}
