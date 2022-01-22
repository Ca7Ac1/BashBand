#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
// #include <time.h>

#include "log.h"
#include "message.h"
#include "input.h"
#include "gui.h"

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
    
    // loop(window, renderer/*, font*/);
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
                        // loop(window, renderer/*, font*/);

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
                        // loop(window, renderer/*, font*/);
                        break;
                    }
                }
            }
            else if (key_event.type == SDL_QUIT) {
                kill_SDL(window, renderer);
            }
        }
    }

    free(keys);
    free(held);

    SDL_Quit();
    exit(0);
}
