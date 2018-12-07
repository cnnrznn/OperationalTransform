#ifndef _OT_CLIENT_H
#define _OT_CLIENT_H

#include "ops.h"

void ot_client_init();
void ot_client_free(void);

void ot_client_set_pid(int pid);

message* ot_client_produce(void);
void ot_client_consume(message*);

void print_pend(FILE *);

#endif /* _OT_CLIENT_H */
