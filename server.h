#ifndef SERVER_H
#define SERVER_H

#define SERVER_ADDR NULL
#define SERVER_PORT "9001"

#include "message.h"

void server();
void handle_message(message msg);

#endif