#include <stdlib.h>
#include <string.h>

#include "ot-client.h"
#include "net-client.h"
#include "ops.h"
#include "queue.h"

static queue *pend;

void
print_pend(FILE *f)
{
        int i;
        operation *op;

        fprintf(f, "{");
        for (i=0; i<pend->n; i++) {
                op = pend->arr[i];
                fprintf(f, "(%d, %c, %u), ", op->type, op->c, op->pos);
        }
        fprintf(f, "}\n");
}

int
ot_client_init()
{
        pend = q_alloc(8);

        return 0;
}

void
ot_client_free()
{
        // meh.
}

/*
 * Get the next pending operation to send to the server.
 */
void
ot_client_drain(void)
{
        //print_pend(stderr);

        // pop element from pending, push to net-client
        operation *op;

        if (NULL != (op = q_peek(pend)) && 0 == net_client_inflight) {
                if (NULLOP != op->type) {
                        net_client_send(op);
                        net_client_inflight = 1;
                }
                else {
                        free(q_pop(pend));
                }
        }
}

/*
 * Receive an operation to apply immediately from the ui.
 */
void
ot_client_put_user_op(operation *op)
{
        // push to pending operations
        q_push(pend, op);

        // apply operation
        op_perform(*op);

        fprintf(stderr, "%u,%u,%d,%c,%u\n", revision, pid, op->type, op->c,
                                                op->pos);
}

/*
 * Receive an operation from the server to transform pending operations against.
 */
void
ot_client_put_serv_msg(message *msg)
{
        operation *pop, newop;
        int i;

        if (pid == msg->pid) {
                net_client_inflight = 0;
                free(q_pop(pend));
                return;
        }

        newop = msg->op;

        // transform all operations in 'pend' against op
        for (i=0; i<pend->n; i++) {
                pop = pend->arr[i];
                newop = op_transform(newop, *pop, msg->pid, pid);
                //fprintf(stderr, "Transform (%d, %c, %u) against (%d, %c, %u)\n",
                //        pop->type, pop->c, pop->pos, op->type, op->c, op->pos);
                *pop = op_transform(*pop, msg->op, pid, msg->pid);
                msg->op = newop;
        }

        // apply op
        op_perform(newop);
}
