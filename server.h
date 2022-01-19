#ifndef SERVER_H
#define SERVER_H

#define SERVER_ADDR NULL
#define SERVER_PORT "9001"

#include "message.h"
#include "connections.h"

void server();
connections *handle_message(connections *c, message msg, int rd);
connections *close_connection(connections *c, message msg, int rd);

#endif
