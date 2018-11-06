#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "entity.h"
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
        int i, j, n, nops=0, index;
        FILE *f;
        char fn[64] = { 0 };
        int optype;
        char c;
        uint32_t pos;
        uint32_t sv[COLLAB_MAX];
        queue **opqs;
        operation *op;

        if (SIG_ERR == signal(SIGINT, sigint_handler)) {
                perror("Setting signal handler");
                abort();
        }

        entity_init();
        srand(time(NULL));
        n = atoi(argv[1]);
        opqs = malloc(n * sizeof(void*));
        for (i=0; i<n; i++)
                opqs[i] = q_alloc(1024);

        fprintf(stderr, "Initialized\n");

        // load "buffer"
        f = fopen("buffer", "r");
        fread(document, DOCSIZE, sizeof(char), f);
        fclose(f);

        fprintf(stderr, "Loaded buffer\n");

        // load "testfile.[0,(N-1)]"
        for (i=0; i<n; i++) {
                sprintf(fn, "testfile.%d", i);
                f = fopen(fn, "r");

                memset(sv, 0, COLLAB_MAX*sizeof(uint32_t));

                while (EOF != fscanf(f, "%d,%c,%u", &optype, &c, &pos)) {
                        op = malloc(sizeof(operation));
                        op->pid = i;
                        memcpy(op->s, sv, COLLAB_MAX * sizeof(uint32_t));
                        op->o.type = optype;
                        op->o.c = c;
                        op->o.pos = pos;

                        q_push(opqs[i], op);

                        fprintf(stderr, "{");
                        for (j=0; j<COLLAB_MAX; j++)
                                fprintf(stderr, "%u, ", sv[j]);
                        fprintf(stderr, "\n");

                        sv[i]++;
                        nops++;
                }

                fclose(f);
        }

        // DEBUG print q
        for (j=0; j<n; j++) {
                fprintf(stderr, "opq.%d = {\n", j);
                for (i=0; i<opqs[j]->n; i++) {
                        op = opqs[j]->arr[i];
                        fprintf(stderr, "\t%d, %c, %u\n", op->o.type, op->o.c, op->o.pos);
                }
                fprintf(stderr, "}\n");
        }

        // receive all ops
        while (nops > 0) {
                index = rand()%n;
        //for (index=0; index<n; index++) {
        //        while (NULL != (op = q_pop(opqs[index]))) {
                if (NULL != (op = q_pop(opqs[index]))) {
                        recv_operation(*op);
                        free(op);

                        nops--;
                }
        }

        fprintf(stderr, "Queue = {\n");
        for (i=0; i<Queue->n; i++) {
                op = Queue->arr[i];
                fprintf(stderr, "\t%u, %d, %c, %u\n", op->pid, op->o.type, op->o.c, op->o.pos);
        }
        fprintf(stderr, "}\n");

        fprintf(stderr, "Received operations\n");

        // execute ops
        while (cont) {
                exec_operations();
                sleep(1);
                document[DOCSIZE-1] = '\0';
                fprintf(stdout, "%s\n\n", document);
                fflush(stdout);
        }

        // results?
        document[DOCSIZE-1] = '\0';
        fprintf(stdout, "%s", document);
        print_state();

        return 0;
}
