#include <stdlib.h>
#include <string.h>

#include "heap.h"
#include "ops.h"

heap Queue;
heap Log;

void
entity_init(void)
{
        heap_init(&Queue, 1024, comp_operation);
        heap_init(&Log, 1024, comp_operation);
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
