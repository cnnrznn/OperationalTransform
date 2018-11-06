#ifndef _ENTITY_H
#define _ENTITY_H

#include "ops.h"
#include "queue.h"

extern uint32_t state[];
extern queue *Log;
extern queue *Queue;

void
entity_init(void);

void
recv_operation(operation op);

void
exec_operations(void);

void
print_state(void);

#endif /* _ENTITY_H */
