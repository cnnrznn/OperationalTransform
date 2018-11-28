#ifndef _OT_SERVER_H
#define _OT_SERVER_H

#include "ops.h"

void print_log(FILE *);

void ot_server_init(void);
void ot_server_free(void);

void ot_server_produce(FILE *stream);
void ot_server_consume(FILE *stream);

#endif /* _OT_SERVER_H */
