#ifndef CLIENT_H
#define CLIENT_H

#define CLIENT_ADDR "127.0.0.1"
#define CLIENT_PORT "9001"
#define NOTES 12

#include <SDL2/SDL.h>

#include "message.h"
#include "synth.h"

void client(char *ip, char *port, char *name);
int open_connection(int *client_socket, char *ip, char *port, char *name);
message *get_server_data();
notes *handle_client_message(notes *n, int rd, message *msg);

#endif