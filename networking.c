#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>

#include "networking.h"
#include "log.h"

int server_setup(char *addr, char *port)
{
    struct addrinfo *hints = calloc(1, sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;

    struct addrinfo *results;
    getaddrinfo(addr, port, hints, &results);

    int server_socket = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
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

int client(char *addr, char *port)
{   
    struct addrinfo *hints = calloc(1, sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;

    struct addrinfo *results;
    getaddrinfo(addr, port, hints, &results);

    int client_socket = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    connect(client_socket, results->ai_addr, results->ai_addrlen);

    return client_socket;
}