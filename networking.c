#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>

#include "networking.h"
#include "message.h"
#include "log.h"

int server_setup(char *addr, char *port)
{
    struct addrinfo *hints = calloc(1, sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;

    struct addrinfo *results;
    getaddrinfo(addr, port, hints, &results);

    int option = 1;
    int server_socket = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    err_info(server_socket, "Server socket creation");

    int bind_err = bind(server_socket, results->ai_addr, results->ai_addrlen);
    err_info(bind_err, "Binding server_socket to address and port");

    free(hints);
    freeaddrinfo(results);

    int listen_err = listen(server_socket, 30);
    err_info(listen_err, "Listen on port");

    return server_socket;
}

int server_connect(int server_socket)
{
    struct sockaddr_storage address;
    socklen_t sock_size = sizeof(address);

    int connection = accept(server_socket, (struct sockaddr *) &address, &sock_size);
    err_info(connection, "accepting incoming client connection");

    return connection;
}

int client_setup(char *addr, char *port)
{
    struct addrinfo *hints = calloc(1, sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;

    struct addrinfo *results;
    getaddrinfo(addr, port, hints, &results);

    int client_socket = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    connect(client_socket, results->ai_addr, results->ai_addrlen);

    free(hints);
    freeaddrinfo(results);

    return client_socket;
}

int read_connections(connections *c)
{
    fd_set readfd;
    FD_ZERO(&readfd);

    int max = 0;
    connections *temp = c;
    while (temp)
    {
        FD_SET(temp->descriptor, &readfd);
        max = temp->descriptor > max ? temp->descriptor : max;

        temp = temp->next;
    }

    int size = select(max + 1, &readfd, NULL, NULL, NULL);
    err_info(size, "read from multiple descriptors");

    while (c)
    {
        if (FD_ISSET(c->descriptor, &readfd))
        {
            return c->descriptor;
        }

        c = c->next;
    }

    err(-1);
    return -1;
}

connections *add_connection(connections *c, int descriptor)
{
    connections *temp = malloc(sizeof(connections));
    temp->descriptor = descriptor;
    temp->next = c;

    return temp;
}

connections *write_connections(connections *c, message msg)
{

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
