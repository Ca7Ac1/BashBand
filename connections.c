#include <stdlib.h>
#include <stdio.h>

#include "connections.h"

connections *add_connection(connections *c, int descriptor)
{
    connections *temp = malloc(sizeof(connections));
    temp->descriptor = descriptor;
    temp->read = 1;
    temp->write = 1;
    temp->next = c;

    return temp;
}

void set_connection(connections *c, int descriptor, char read, char write)
{
    while (c)
    {
        if (c->descriptor == descriptor)
        {
            c->read = read;
            c->write = write;

            return c;
        }
    }
}

connections *remove_connection(connections *c, int descriptor)
{
    if (c && c->descriptor == descriptor)
    {
        connections *temp = c;
        c = c-> next;
        free(temp);

        return c;
    }

    while (c->next)
    {
        if (c->next->descriptor == descriptor)
        {
            connections *temp = c->next;
            c->next = c->next->next;
            free(temp);

            return c;
        }

        c = c->next;
    }

    return c;
}

connections *free_connections(connections *c)
{
    while (c)
    {
        connections *temp = c;
        c = c-> next;
        free(temp);
    }

    return NULL;
}

void print_connections(connections *c)
{
    while (c)
    {
        printf("descriptor: %d \n", c->descriptor);
        c = c->next;
    }  
}