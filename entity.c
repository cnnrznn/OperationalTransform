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
receive_op(operation op)
{
        operation *newop = malloc(sizeof(operation));
        memcpy(newop, &op, sizeof(operation));

        q_push(Queue, newop);
}

void
exec_op(void)
{
        operation *op, us;
        memcpy(us.s, state, COLLAB_MAX*sizeof(uint32_t));

        for (i=0; i<Queue->n; i++) {
                op = Queue->arr[i];

                if (comp_operation(op, &us) < 0)
                        continue;
                if (0 == comp_operation(op, &us))
                        goto exec;

                // transform operation
                for (j=Log->n-1; j>=0; j--) {
                        lop = Log->arr[i];
                        if (comp_operation(lop, op) >= 0)
                                break;
                }
                for (; j<Log->n; j++) {
                        // transform op
                }

exec:
                // 1. remove operation from queue
                q_remove(Queue, i);
                op_perform(op);
                memcpy(op->s, state, COLLAB_MAX*sizeof(uint32_t)); // op performed at OUR clock
                q_push(Log, op);
                state[op->pid]++;
        }
}
