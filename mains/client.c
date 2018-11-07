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
        signal(SIGINT, sigint_handler);

        doc_client_init();
        net_client_init();

        while (cont) {
                fprintf(stderr, "Client loop\n");
        }

        net_client_free();
        doc_client_free();

        print_log(stdout);

        return 0;
}
