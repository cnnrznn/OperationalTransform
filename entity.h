#ifndef _ENTITY_H
#define _ENTITY_H

#include "ops.h"

extern uint32_t state[];

void
entity_init(void);

void
recv_operation(operation op);

void
exec_operations(void);

#endif /* _ENTITY_H */
