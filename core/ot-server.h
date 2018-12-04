#ifndef _OT_SERVER_H
#define _OT_SERVER_H

#include "ops.h"

void print_log(FILE *);

void ot_server_init(void);
void ot_server_free(void);

message* ot_server_produce(void);
void ot_server_consume(message*);

#endif /* _OT_SERVER_H */
