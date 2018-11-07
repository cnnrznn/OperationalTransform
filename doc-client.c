#include <stdlib.h>

#include "doc-client.h"
#include "net-client.h"
#include "ops.h"
#include "queue.h"

static queue *pend;

static uint32_t pid;
static uint32_t rev;

void
doc_client_init()
{
        pend = q_alloc(8);
}

void
doc_client_free()
{
        // meh.
}

/*
 * Get the next pending operation to send to the server.
 */
void
doc_client_drain(void)
{
        // pop element from pending, push to net-client
        op *o;

        if (NULL != (o = q_peek(pend)) && 0 == net_client_inflight) {
                q_pop(pend);
                net_client_send(o);
        }

        free(o);
}

/*
 * Receive an operation to apply immediately from the ui.
 */
void
doc_client_put_user_op(op *o)
{
        // push to pending operations
        q_push(pend, o);

        // apply operation
        op_perform(*o);
}

/*
 * Receive an operation from the server to transform pending operations against.
 */
void
doc_client_put_serv_op(op *o)
{
        op *p;
        int i;

        // transform all operations in 'pend' against op
        for (i=0; i<pend->n; i++) {
                p = pend->arr[i];
                *p = op_transform(*p, *o);
        }

        // apply op
        op_perform(*o);
}
