#ifndef _NET_SERVER_H
#define _NET_SERVER_H

int net_server_init(void);
void net_server_free(void);

void net_server_drain(void);
void net_server_broadcast(message *);

#endif /* _NET_SERVER_H */
