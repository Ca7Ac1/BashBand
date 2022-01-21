#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "gui.h"

void init(SDL_Window* window, SDL_Renderer* renderer) {
    window = SDL_CreateWindow("Bash", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 540, SDL_WINDOW_SHOWN);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
}

int loop(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_QUIT:
                return 0;
                break;
        }
    }

    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = 300;
    r.h = 300;
    SDL_RenderFillRect(renderer, &r);

    for(int i = 0; i < 10; i++) {
        double x = 160+100.0*i;
        double y = 100.0;
        draw_white_key(renderer, x,y);
    }
    


    SDL_RenderPresent(renderer);
    return 1;
}

void kill(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void draw_white_key(SDL_Renderer* renderer, double x, double y) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = 100;
    r.h = 600;
    SDL_RenderFillRect(renderer, &r);
}

void draw_black_key(SDL_Renderer* renderer, double x, double y) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = 60;
    r.h = 400;
    SDL_RenderFillRect(renderer, &r);
}