#ifndef CLIENT_H
#define CLIENT_H

#define CLIENT_ADDR "127.0.0.1"
#define CLIENT_PORT "9001"
#define NOTES 12

#include <SDL2/SDL.h>

#include "message.h"
#include "synth.h"

// this name is beautiful appreciate it pls
typedef struct key
{
    char button;
    // C#4 null
    char note[4];
} key;

void client(char *ip, char *port, char *name);
int open_connection(int *client_socket, char *ip, char *port, char *name);
message *get_server_data();
notes *handle_client_message(notes *n, int rd, message *msg);
key *setup_notes();
int get_note_pressed(SDL_Event event, key *keys);
notes *play_input(notes *n, int client_socket, char *note, char *instrument, int id);
notes *stop_input(notes *n, int client_socket, char *note, char *instrument, int id);

#endif