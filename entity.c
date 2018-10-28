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

        while (NULL != (op = q_pop(Queue))) {
                if (1 == comp_operation(op, &us)) {
                        // do operational transforms
                }

                op_perform(op);
                q_push(Log, op);
                state[op->pid]++;
        }
}
