#include <stdlib.h>

#include "connections.h"

connections *add_connection(connections *c, int descriptor)
{
    connections *temp = malloc(sizeof(connections));
    temp->descriptor = descriptor;
    temp->next = c;

    return temp;
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
