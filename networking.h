#ifndef NETWORKING_H
#define NETWORKING_H

#include <sys/select.h>

#include "message.h"

typedef struct connections
{
    int descriptor;
    struct connections *next;
} connections;

int server_setup(char *addr, char *port);
int server_connect(int server_socket);
int client_setup(char *addr, char *port);
int read_connections(connections *c);
int write_connections(connections *c, int *exclude )
connections *add_connection(connections *c, int descriptor);
connections *remove_connection(connections *c, int id);
connections *free_connections(connections *c);

#endif
