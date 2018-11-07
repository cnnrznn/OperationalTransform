#ifndef _NET_CLIENT_H
#define _NET_CLIENT_H

extern char net_client_inflight;

int net_client_init(void);
void net_client_free(void);

void net_client_send(op *);
void net_client_drain(void);

#endif /* _NET_CLIENT_H */
