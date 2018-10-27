#ifndef _ENTITY_H
#define _ENTITY_H

#include "heap.h"
#include "ops.h"

extern heap Queue;
extern heap Log;

void
entity_init(void);

void
receive_op(operation op);

void
exec_op(void);

#endif /* _ENTITY_H */
