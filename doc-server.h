#ifndef _DOC_SERVER_H
#define _DOC_SERVER_H

#include "ops.h"

void print_log(FILE *);

void put_operation(operation *);
void process_pending(void);

#endif /* _DOC_SERVER_H */
