#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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

            return;
        }

        c = c->next;
    }
}

connections *remove_connection(connections *c, int descriptor)
{
    if (!c)
    {
        return c;
    }

    close(descriptor);
    
    if (c->descriptor == descriptor)
    {
        connections *temp = c;
        c = c->next;
        free(temp);

        return c;
    }

    connections *head = c;
    while (c->next)
    {
        if (c->next->descriptor == descriptor)
        {
            connections *temp = c->next;
            c->next = c->next->next;
            free(temp);

            return head;
        }

        c = c->next;
    }

    return head;
}

connections *free_connections(connections *c)
{
    while (c)
    {
        connections *temp = c;
        c = c->next;
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