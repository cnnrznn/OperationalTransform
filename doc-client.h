#ifndef _DOC_CLIENT_H
#define _DOC_CLIENT_H

#include "ops.h"

void doc_client_init();
void doc_client_free();

op * get_pend_op();
void put_user_op();
void pus_serv_op();

#endif /* _DOC_CLIENT_H */
