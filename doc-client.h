#ifndef _DOC_CLIENT_H
#define _DOC_CLIENT_H

#include "ops.h"

void doc_client_init();
void doc_client_free();

op * doc_client_get_pend_op();
void doc_client_put_user_op(op *);
void doc_client_pus_serv_op(op *);

#endif /* _DOC_CLIENT_H */
