#ifndef _OT_CLIENT_H
#define _OT_CLIENT_H

#include "ops.h"

void ot_client_init(int pid);
void ot_client_free(void);

message* ot_client_produce(void);
void ot_client_consume(message*);

void print_pend(FILE *);

#endif /* _OT_CLIENT_H */
