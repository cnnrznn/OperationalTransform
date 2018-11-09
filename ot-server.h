#ifndef _DOC_SERVER_H
#define _DOC_SERVER_H

#include "ops.h"

void print_log(FILE *);

void doc_server_init(void);
void doc_server_free(void);

void doc_server_put_op(message *);
void doc_server_drain(void);

#endif /* _DOC_SERVER_H */
