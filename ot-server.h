#ifndef _OT_SERVER_H
#define _OT_SERVER_H

#include "ops.h"

void print_log(FILE *);

void ot_server_init(void);
void ot_server_free(void);

void ot_server_put_op(message *);
void ot_server_drain(void);

#endif /* _OT_SERVER_H */
