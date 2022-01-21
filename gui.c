#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "gui.h"

void init(SDL_Window** window, SDL_Renderer** renderer) {
    SDL_Window* twindow = SDL_CreateWindow("Bash", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 540, SDL_WINDOW_SHOWN);
    
    SDL_Renderer* trenderer = SDL_CreateRenderer(twindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(trenderer, 0, 0, 0, 255);
	SDL_RenderClear(trenderer);

    *window = twindow;
    *renderer = trenderer;
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
    
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_RenderClear( renderer );

    // white keys
    for(int i = 0; i < 8; i++) {
        double x = 80+100*i;
        double y = 70;
        draw_white_key(renderer, x,y);
    }

    // black keys
    for(int i = 0; i < 2; i++) {
        double x = 80+70+100*i;
        double y = 70;
        draw_black_key(renderer, x, y);
    }
    for(int i = 0; i < 3; i++) {
        double x = 380+70+100*i;
        double y = 70;
        draw_black_key(renderer, x, y);
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
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = 100;
    r.h = 400;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &r);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &r);
}

void draw_black_key(SDL_Renderer* renderer, double x, double y) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = 60;
    r.h = 250;
    SDL_RenderFillRect(renderer, &r);
}