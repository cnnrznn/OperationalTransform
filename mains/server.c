#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "doc-server.h"
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

        doc_server_init();
        net_server_init();

        while (cont) {
                fprintf(stderr, "Server loop\n");
                net_server_drain();
                doc_server_drain();
        }

        net_server_free();
        doc_server_free();

        print_log(stdout);

        return 0;
}
