#ifndef _ENTITY_H
#define _ENTITY_H

#include "ops.h"

void
entity_init(void);

void
receive_op(operation op);

void
exec_op(void);

#endif /* _ENTITY_H */
