#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <SDL.h>

#include "log.h"
#include "synth.h"
#include "input.h"
#include "gui.h"

int main()
{
    // input();
    SDL_Window * window;
    SDL_Renderer * renderer;

    init(window, renderer);
    
    printf("%s %s\n", window, renderer);

    while (loop(window, renderer)) { 
        SDL_Delay(10); 
    }

    kill(window, renderer);

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
