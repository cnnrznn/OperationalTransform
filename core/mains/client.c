#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "ot-client.h"
#include "ops.h"
#include "queue.h"

int main(int argc, char **argv)
{
        int pid;

        if (argc < 3) {
                fprintf(stderr, "Usage: ./client <pid> <revision>\n");
                exit(1);
        }

        pid = atoi(argv[1]);
        revision = atoi(argv[2]);

        if (ot_client_init(pid))
                goto cleanup;

        while (1) {
                ot_client_consume(stdin);
                ot_client_produce(stdout);
        }

cleanup:
        ot_client_free();

        return 0;
}
