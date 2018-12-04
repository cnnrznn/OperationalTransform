#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "ot-server.h"
#include "ops.h"
#include "queue.h"

int main(int argc, char **argv)
{
        ot_server_init();

        while (1) {
                //ot_server_consume(stdin);
                //ot_server_produce(stdout);
                break;
        }

        ot_server_free();

        return 0;
}
