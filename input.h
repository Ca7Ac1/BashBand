#ifndef INPUT_H
#define INPUT_H

#define NOTES 13

#include <SDL2/SDL.h>

#include "message.h"
#include "synth.h"
#include "settings.h"

int get_note_pressed(SDL_Event event, key *keys, char settings);
notes *play_input(notes *n, int client_socket, char *note, char *instrument, int id);
notes *stop_input(notes *n, int client_socket, char *note, char *instrument, int id);
notes *stop_all_notes(notes *n, int client_socket);

#endif
