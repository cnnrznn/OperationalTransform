#ifndef _OT_CLIENT_H
#define _OT_CLIENT_H

#include "ops.h"

int ot_client_init(int pid);
void ot_client_free(void);

void ot_client_produce(FILE *stream);
void ot_client_consume(FILE *stream);

void print_pend(FILE *);

#endif /* _OT_CLIENT_H */
