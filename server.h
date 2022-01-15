#ifndef SERVER_H
#define SERVER_H

#define SERVER_ADDR NULL
#define SERVER_PORT "9001"

#include "message.h"

void server();
void handle_message(connections *c, message msg, int rd);
void close_connection(connections *c, message msg, int rd);

#endif