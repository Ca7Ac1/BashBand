#ifndef CONNECTIONS_H
#define CONNECTIONS_H

typedef struct connections
{
    int descriptor;
    char read;
    char write;
    struct connections *next;
} connections;

connections *add_connection(connections *c, int descriptor);
void set_connection(connections *c, int descriptor, char read, char write);
connections *remove_connection(connections *c, int id);
connections *free_connections(connections *c);
void print_connections(connections *c);

#endif
