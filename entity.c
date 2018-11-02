#include <stdlib.h>
#include <string.h>

#include "ops.h"
#include "queue.h"

queue *Queue;
queue *Log;

uint32_t state[COLLAB_MAX] = { 0 };

void
entity_init(void)
{
        Queue = q_alloc(1024);
        Log = q_alloc(1024);
}

void
recv_operation(operation op)
{
        operation *newop = malloc(sizeof(operation));
        memcpy(newop, &op, sizeof(operation));

        q_push(Queue, newop);
}

void
exec_operations(void)
{
        int i, j;
        operation *op, us, *lop=NULL;
        memcpy(us.s, state, COLLAB_MAX*sizeof(uint32_t));

        for (i=0; i<Queue->n; i++) {
                op = Queue->arr[i];

                if (comp_operation(op, &us) < 0)
                        continue;                       // 'future' operation (sending site has executed other ops that we haven't
                if (0 == comp_operation(op, &us))
                        goto exec;                      // clocks are the same, i.e. op executed at the same logical time

                // operation happened in the past, must tranform in order to execute now

                // find most recent log entry where the clock is <= op's
                for (j=Log->n-1; j>=0; j--) {
                        if (comp_operation(Log->arr[i], op) >= 0) {
                                lop = Log->arr[i];
                                break;
                        }
                }

                // do transformation
                while (NULL != lop && NULLOP != op->o.type) {
                        // transform op
                        if (op->s[lop->pid] <= lop->s[lop->pid])
                                op->o = op_transform(op->o, lop->o, op->pid, lop->pid);

                        // next Log op
                        lop = (j < Log->n) ? Log->arr[++j] : NULL;
                }

exec:
                // 1. remove operation from queue
                q_remove(Queue, i);
                i--;

                op_perform(op);
                memcpy(op->s, state, COLLAB_MAX*sizeof(uint32_t)); // op performed at OUR clock
                q_push(Log, op);
                state[op->pid]++;
        }
}
