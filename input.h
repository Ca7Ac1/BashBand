#ifndef INPUT_H
#define INPUT_H

#define NOTES 12

#include "message.h"
#include "synth.h"

// this name is beautiful appreciate it pls
typedef struct key
{
    char button;
    // C#4 null
    char note[4];
} key;

key *setup_notes();
int get_note_pressed(SDL_Event event, key *keys);
notes *play_input(notes *n, int client_socket, char *note, char *instrument, int id);
notes *stop_input(notes *n, int client_socket, char *note, char *instrument, int id);

#endif
