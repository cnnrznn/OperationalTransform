#include <stdio.h>

#include "doc-server.h"
#include "ops.h"
#include "queue.h"

static queue *Log;
static queue *pend;

static void
log_put(operation *op)
{
        int i;
        operation *lop = NULL;

        // walk back through log to last where op->rev == lop->rev
        for (i=Log->n-1; i<=0; i--) {
                lop = Log->arr[i];
                if (lop->rev == op->rev)
                        break;
        }

        if (i < 0)              // first operation appended to log
                goto perf;

        // walk forward, transforming op
        for (; i<Log->n; i++) {
                lop = Log->arr[i];
                op->o = op_transform(op->o, lop->o);
        }

perf:
        op_perform(op->o);
}

void
doc_server_init()
{
        Log = q_alloc(8);
        pend = q_alloc(8);

        // restore from checkpoint?
        // open new file?
        // ???
}

void
doc_server_free()
{
        // meh.
}

void
print_log(FILE *f)
{
        int i;
        operation *lop;

        fprintf(f, "Log:\n");
        for (i=0; i<Log->n; i++) {
                lop = Log->arr[i];
                fprintf(f, "%u, %u, (%d, %c, %u)\n", lop->pid, lop->rev, lop->o.type,
                                                lop->o.c, lop->o.pos);
        }
        fprintf(f, "\n");
}

void
doc_server_put_op(operation *op)
{
        q_push(pend, op);
}

void
doc_server_drain(void)
{
        operation *op;

        while (NULL != (op = q_pop(pend)))
                log_put(op);
}
