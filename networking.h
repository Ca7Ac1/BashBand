#ifndef NETWORKING_H
#define NETWORKING_H

int server_setup(char *addr, char *port);
int server_connect(int server_socket);
int client(char *addr, char *port);

#endif