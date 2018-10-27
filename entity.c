#include <stdlib.h>
#include <string.h>

#include "heap.h"
#include "ops.h"
#include "queue.h"

heap Queue;
queue *Log;

uint32_t state[COLLAB_MAX] = { 0 };

void
entity_init(void)
{
        heap_init(&Queue, 1024, comp_operation);
        Log = q_alloc(1024);
}

void
receive_op(operation op)
{
        operation *newop = malloc(sizeof(operation));
        memcpy(newop, &op, sizeof(operation));

        heap_insert(&Queue, newop);
}

void
exec_op(void)
{
}
