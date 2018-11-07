#ifndef _DOC_CLIENT_H
#define _DOC_CLIENT_H

#include "ops.h"

void doc_client_init();
void doc_client_free();

void doc_client_drain();
void doc_client_put_user_op(operation *);
void doc_client_pus_serv_op(operation *);

#endif /* _DOC_CLIENT_H */
