#include <stdio.h>
#include <stdlib.h>

#include "ot-server.h"
#include "ops.h"
#include "queue.h"

static queue *Log;
static queue *pend;

/*
 * Print the Log.
 * Utility function for debugging.
 */
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

static message *
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
                msg->op = op_transform(msg->op, lmsg->op, msg->pid, lmsg->pid);
        }

perf:
        if (NULLOP != msg->op.type)
                revision++;
        msg->rev = revision;

        q_push(Log, msg);

        return msg;
}

/*
 * Initialize this module.
 */
void
ot_server_init()
{
        Log = q_alloc(8);
        pend = q_alloc(8);
}

/*
 * Destroy this module.
 */
void
ot_server_free()
{
        q_free(Log);
        q_free(pend);
}

/*
 * Process all the messages on the pending
 * queue and produce the results on the stream.
 */
message *
ot_server_produce(void)
{
        message *msg;

        if (NULL != (msg = q_pop(pend)))
                return log_put(msg);

        return NULL;
}

/*
 * Read as many messages from the stream and push
 * to the pending queue
 */
void
ot_server_consume(message *msg)
{
        message *newMsg;

        newMsg = malloc(sizeof(message));
        newMsg->pid = msg->pid;
        newMsg->rev = msg->rev;
        newMsg->op.type = msg->op.type;
        newMsg->op.c = msg->op.c;
        newMsg->op.pos = msg->op.pos;

        q_push(pend, newMsg);
}
