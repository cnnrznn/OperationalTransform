#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "ot-server.h"
#include "ops.h"
#include "net-server.h"
#include "queue.h"

static char cont = 1;

static void
sigint_handler(int sig)
{
        cont = 0;
}

int main(int argc, char **argv)
{
        signal(SIGINT, sigint_handler);

        memset(document, ' ', DOCSIZE);

        ot_server_init();
        net_server_init();

        while (cont) {
                fprintf(stderr, "Server loop\n");
                net_server_drain();
                ot_server_drain();

                print_log(stderr);
                print_document(stderr);
        }

        net_server_free();
        ot_server_free();

        return 0;
}
