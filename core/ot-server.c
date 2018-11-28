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

static void
log_put(message *msg, FILE *stream)
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

        fprintf(stream, "%d,%u,%d,%c,%u\n", msg->pid, msg->rev, msg->op.type, msg->op.c,
                                                msg->op.pos);
        fprintf(stderr, "produced: %d,%u,%d,%c,%u\n", msg->pid, msg->rev, msg->op.type, msg->op.c,
                                                msg->op.pos);
        fflush(stream);
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
void
ot_server_produce(FILE *stream)
{
        message *msg;

        while (NULL != (msg = q_pop(pend)))
                log_put(msg, stream);
}

/*
 * Read as many messages from the stream and push
 * to the pending queue
 */
void
ot_server_consume(FILE *stream)
{
        message msg, *newMsg;

        while (5 == fscanf(stream, "%d,%u,%d,%c,%u", &msg.pid, &msg.rev,
                                                &msg.op.type, &msg.op.c, &msg.op.pos)) {
                if (msg.pid < 0)
                        break;

                newMsg = malloc(sizeof(message));
                newMsg->pid = msg.pid;
                newMsg->rev = msg.rev;
                newMsg->op.type = msg.op.type;
                newMsg->op.c = msg.op.c;
                newMsg->op.pos = msg.op.pos;

                q_push(pend, newMsg);

                fprintf(stderr, "consumed: %d,%u,%d,%c,%u\n", msg.pid, msg.rev, msg.op.type,
                                                        msg.op.c, msg.op.pos);
        }
}
