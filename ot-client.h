#ifndef _OT_CLIENT_H
#define _OT_CLIENT_H

#include "ops.h"

void ot_client_init();
void ot_client_free();

void ot_client_drain();
void ot_client_put_user_op(operation *);
void ot_client_pus_serv_op(operation *);

#endif /* _OT_CLIENT_H */
