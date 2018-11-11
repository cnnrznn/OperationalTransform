#include <stdio.h>
#include <stdlib.h>

#include "ot-server.h"
#include "net-server.h"
#include "ops.h"
#include "queue.h"

static queue *Log;
static queue *pend;

uint32_t revision = 0;

static void
log_put(message *msg)
{
        int i;
        message *lmsg;

        // walk back through log to last where op->rev == lmsg->rev
        for (i=Log->n-1; i>=0; i--) {
                lmsg = Log->arr[i];
                if (lmsg->rev == msg->rev)
                        break;
        }

        // walk forward, transforming op
        for (i+=1; i<Log->n; i++) {
                lmsg = Log->arr[i];
                msg->op = op_transform(msg->op, lmsg->op);
        }

perf:
        revision++;
        op_perform(msg->op);
        msg->rev = revision;
        net_server_broadcast(msg);
        q_push(Log, msg);
}

void
ot_server_init()
{
        Log = q_alloc(8);
        pend = q_alloc(8);

        // restore from checkpoint?
        // open new file?
        // ???
}

void
ot_server_free()
{
        // meh.
}

void
print_log(FILE *f)
{
        int i;
        message *lmsg;

        fprintf(f, "Log:\n");
        for (i=0; i<Log->n; i++) {
                lmsg = Log->arr[i];
                fprintf(f, "%u, %u, (%d, %c, %u)\n", lmsg->pid, lmsg->rev, lmsg->op.type,
                                                lmsg->op.c, lmsg->op.pos);
        }
        fprintf(f, "\n");
}

void
ot_server_put_op(message *msg)
{
        q_push(pend, msg);
}

void
ot_server_drain(void)
{
        message *msg;

        while (NULL != (msg = q_pop(pend)))
                log_put(msg);
}
