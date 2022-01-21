#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <SDL2/SDL.h>

#include "log.h"
#include "synth.h"
#include "input.h"

int main()
{
    setup_log(STDOUT_FILENO);

    SDL_Init(SDL_INIT_VIDEO);
    // SDL_EnableUNICODE(1);

    SDL_Window *win = SDL_CreateWindow("input", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN);
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Event key_event;

    printf("%d\n", getpid());
    while (1)
    {
        while (SDL_PollEvent(&key_event))
        {
            if (key_event.type == SDL_KEYDOWN)
            {
                SDL_KeyboardEvent *key = &key_event.key;
                const char *keystroke = SDL_GetKeyName(key->keysym.sym);
                printf("%s pressed\n", keystroke);

                if (keystroke[0] == 'q')
                {
                    SDL_Quit();
                    exit(0);
                }
            }
            else if (key_event.type == SDL_KEYUP)
            {
                SDL_KeyboardEvent *key = &key_event.key;
                const char *keystroke = SDL_GetKeyName(key->keysym.sym);
                printf("%s released\n", keystroke);
            }
        }
    }

    SDL_Quit();
    // input();

    // while (1) {}
    // int pid = 0;

    // key *notes = setup_notes();

    // // printf("%s\n", notes);

    // while (1)
    // {
    //     input(notes);
    // }

    // return 0;
}
