#ifndef NETWORKING_H
#define NETWORKING_H

#include <sys/select.h>

typedef struct connections 
{
    int descriptor;
    int id;
    struct connections *next;
} connections;

int server_setup(char *addr, char *port);
int server_connect(int server_socket);
int client_setup(char *addr, char *port);
int read_connections(connections *c);
connections *add_connection(connections *c, int descriptor, int id);
connections *remove_connection(connections *c, int id);
connections *free_connections(connections *c);

#endif