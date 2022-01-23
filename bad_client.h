#ifndef BAD_CLIENT_H
#define BAD_CLIENT_H

#define CLIENT_ADDR "127.0.0.1"
#define CLIENT_PORT "9001"

#include "message.h"

void client(char *ip, char *port, char *name);

#endif