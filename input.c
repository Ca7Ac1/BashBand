#include <unistd.h>
#include <fcntl.h>
#include <SDL2/SDL.h>

#include "input.h"
#include "synth.h"
#include "log.h"

key *setup_notes()
{
    // if(file == NULL) {
    // 0: C, 1: C#, 2: D, 3: D#, 4: E, 5: F, 6: F#, 7: G, 8: G#, 9: A, 10: A#, 11: B

    key *key_notes = malloc(sizeof(key) * NOTES);
    key_notes[0] = (key){.button = 'Z', .note = "C"};
    key_notes[1] = (key){.button = 'S', .note = "C#"};
    key_notes[2] = (key){.button = 'X', .note = "D"};
    key_notes[3] = (key){.button = 'D', .note = "D#"};
    key_notes[4] = (key){.button = 'C', .note = "E"};
    key_notes[5] = (key){.button = 'V', .note = "F"};
    key_notes[6] = (key){.button = 'G', .note = "F#"};
    key_notes[7] = (key){.button = 'B', .note = "G"};
    key_notes[8] = (key){.button = 'H', .note = "G#"};
    key_notes[9] = (key){.button = 'N', .note = "A"};
    key_notes[10] = (key){.button = 'J', .note = "A#"};
    key_notes[11] = (key){.button = 'M', .note = "B"};

    return key_notes;
}

int get_note_pressed(SDL_Event event, key *keys)
{
    SDL_KeyboardEvent *key = &event.key;
    char keystroke = SDL_GetKeyName(key->keysym.sym)[0];

    for (int i = 0; i < NOTES; i++)
    {
        if (keys[i].button == keystroke)
        {
            return i;
        }
    }

    return -1;
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