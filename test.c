#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "log.h"
#include "synth.h"
#include "input.h"
#include "gui.h"

int main()
{
    // input();
    // srand(time(NULL));
    SDL_Window * window;
    SDL_Renderer * renderer;

    init(&window, &renderer);

    TTF_Font* font;
    font = TTF_OpenFont("fonts/OpenSans-Regular.ttf", 24);
    

    while (loop(window, renderer/*, font*/)) { 
        SDL_Delay(10); 
    }

    kill_SDL(window, renderer);

    // setup_log(STDOUT_FILENO);
    // int pid = 0;

    // key *notes = setup_notes();

    // // printf("%s\n", notes);

    // while (1)
    // {
    //     input(notes);
    // }

    return 0;
}
