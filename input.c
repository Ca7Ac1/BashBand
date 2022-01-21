#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
// #include <time.h>

#include "log.h"
#include "message.h"
#include "input.h"

key *setup_notes()
{
    // if(file == NULL) {
    // 0: C, 1: C#, 2: D, 3: D#, 4: E, 5: F, 6: F#, 7: G, 8: G#, 9: A, 10: A#, 11: B

    key *key_notes = malloc(sizeof(key) * NOTES);
    key_notes[0] = (key){.button = 'z', .note = "C"};
    key_notes[1] = (key){.button = 's', .note = "C#"};
    key_notes[2] = (key){.button = 'x', .note = "D"};
    key_notes[3] = (key){.button = 'd', .note = "D#"};
    key_notes[4] = (key){.button = 'c', .note = "E"};
    key_notes[5] = (key){.button = 'v', .note = "F"};
    key_notes[6] = (key){.button = 'g', .note = "F#"};
    key_notes[7] = (key){.button = 'b', .note = "G"};
    key_notes[8] = (key){.button = 'h', .note = "G#"};
    key_notes[9] = (key){.button = 'n', .note = "A"};
    key_notes[10] = (key){.button = 'j', .note = "A#"};
    key_notes[11] = (key){.button = 'm', .note = "B"};

    return key_notes;
}

int isKeyDown(char c) {
    // return rand() & 1;
    return 0;
}

int input()
{
    int pipe_des[2];
    pipe(pipe_des);

    int c = fork();
    err(c);

    if (c)
    {
        close(pipe_des[1]);
        return pipe_des[0];
    }

    close(pipe_des[0]);
    int output = pipe_des[1];

    key *keys = setup_notes();
    char *held = calloc(1, NOTES * sizeof(char));

    SDL_Event key_event;

    char instrument[10];
    strcpy(instrument, "sin");

    // test
    // note_message data;
    // data.note_id[0] = 'p';
    // strcpy(data.note, "C");
    // strcpy(data.instrument, "sin");
    // write(output, &data, sizeof(note_message));

    // data.note_id[0] = 's';
    // strcpy(data.note, "C");
    // strcpy(data.instrument, "sin");
    // write(output, &data, sizeof(note_message));
    //

    while (1)
    {
        while (SDL_PollEvent(&key_event))
        {
            if (key_event.type == SDL_KEYDOWN)
            {
                SDL_KeyboardEvent *key = &key_event.key;
                char keystroke = SDL_GetKeyName(key->keysym.sym)[0];

                for (int i = 0; i < NOTES; i++)
                {
                    if (keys[i].button == keystroke && held[i] == 0)
                    {
                        held[i] = 1;

                        note_message data;
                        data.note_id[0] = 'p';
                        strcpy(data.note, keys[i].note);
                        strcpy(data.instrument, instrument);

                        write(output, &data, sizeof(note_message));

                        break;
                    }
                }
            }
            else if (key_event.type == SDL_KEYUP)
            {
                SDL_KeyboardEvent *key = &key_event.key;
                char keystroke = SDL_GetKeyName(key->keysym.sym)[0];

                for (int i = 0; i < NOTES; i++)
                {
                    if (keys[i].button == keystroke)
                    {
                        held[i] = 0;

                        note_message data;
                        data.note_id[0] = 's';
                        strcpy(data.note, keys[i].note);
                        strcpy(data.instrument, instrument);

                        write(output, &data, sizeof(note_message));

                        break;
                    }
                }
            }
        }
    }

    free(keys);
    free(held);

    SDL_Quit();
    exit(0);
}
