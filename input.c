#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "input.h"
#include "synth.h"
#include "log.h"

int get_note_pressed(SDL_Event event, key *keys, char settings)
{
    SDL_KeyboardEvent *key = &event.key;
    char keystroke = SDL_GetKeyName(key->keysym.sym)[0];
    // printf("key: %c\n", keystroke);

    if (keystroke == settings)
    {
        return -1;
    }

    for (int i = 0; i < NOTES; i++)
    {
        if (keys[i].button == keystroke)
        {
            return i;
        }
    }

    return -2;
}

notes *play_input(notes *n, int client_socket, char *note, char *instrument, int id)
{
    char msg_id[25];
    sprintf(msg_id, "%d-%s-%s", id, instrument, note);

    n = add_note(n, instrument, note, msg_id);

    message msg;
    msg.type = PLAY_NOTE_MSG;

    note_message *data = &msg.data.note_data;
    strcpy(data->instrument, instrument);
    strcpy(data->note, note);
    strcpy(data->note_id, msg_id);

    write(client_socket, &msg, sizeof(msg));

    return n;
}

notes *stop_input(notes *n, int client_socket, char *note, char *instrument, int id)
{
    char msg_id[25];
    sprintf(msg_id, "%d-%s-%s", id, instrument, note);

    n = remove_note(n, msg_id);

    message msg;
    msg.type = STOP_NOTE_MSG;

    stop_message *data = &msg.data.stop_data;
    strcpy(data->note_id, msg_id);

    write(client_socket, &msg, sizeof(message));

    return n;
}

notes *stop_all_notes(notes *n, int client_socket)
{
    notes *temp = n;

    while (temp)
    {
        message msg;
        msg.type = STOP_NOTE_MSG;

        stop_message *data = &msg.data.stop_data;
        strcpy(data->note_id, temp->id);

        write(client_socket, &msg, sizeof(message));

        temp = temp->next;
    }

    return free_notes(n);
}