#ifndef NETWORKING_H
#define NETWORKING_H

#include <sys/select.h>

#include "message.h"
#include "connections.h"

int server_setup(char *addr, char *port);
int server_connect(int server_socket);
int client_setup(char *addr, char *port);
int read_connections(connections *c);
void write_connections(connections *c, message msg);

#endif
