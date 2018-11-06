#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "doc-client.h"
#include "ops.h"
#include "queue.h"

#define TESTSIZE 10000

static char cont = 1;

void
sigint_handler(int sig)
{
        cont = 0;
}

char
bozosort(void *a, void *b)
{
        return (rand() % 3) - 1;
}

int main(int argc, char **argv)
{

        return 0;
}
