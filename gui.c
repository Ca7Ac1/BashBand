#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>

#include "gui.h"
#include "input.h"

char* buttons = "zxcvbnm,sdghj";

void init(SDL_Window** window, SDL_Renderer** renderer) {
    SDL_Init( SDL_INIT_EVERYTHING );
    // TTF_Init();
    SDL_Window* twindow = SDL_CreateWindow("Bash", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 540, SDL_WINDOW_SHOWN);

    SDL_Renderer* trenderer = SDL_CreateRenderer(twindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(trenderer, 0, 0, 0, 255);
	SDL_RenderClear(trenderer);

    *window = twindow;
    *renderer = trenderer;
}


int loop(SDL_Window* window, SDL_Renderer* renderer/*, TTF_Font* font*/ ) {
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
        char c[2];
        c[0] = buttons[i];
        c[1] = '\0';
        if(isKeyDown(c[0])) draw_white_key(renderer, x,y, c[0], 1);
        else draw_white_key(renderer, x,y, c[0], 0);
        // SDL_Color color = { 0, 0, 0 };
        // draw_char(x+45, y+300, font, c, color, renderer);
    }

    // black keys
    for(int i = 0; i < 2; i++) {
        double x = 80+70+100*i;
        double y = 70;
        char c[2];
        c[0] = buttons[8+i];
        c[1] = '\0';
        if(isKeyDown(c[0])) {
            draw_black_key(renderer, x, y, c[0], 1);
            // SDL_Color color = { 0, 0, 0 };
            // draw_char(x+22, y+150, font, c, color, renderer);
        } else {
            draw_black_key(renderer, x, y, c[0], 0);
            // SDL_Color color = { 255, 255, 255 };
            // draw_char(x+22, y+150, font, c, color, renderer);
        }
    }
    for(int i = 0; i < 3; i++) {
        double x = 380+70+100*i;
        double y = 70;
        char c[2];
        c[0] = buttons[8+2+i];
        c[1] = '\0';
        if(isKeyDown(c[0])) {
            draw_black_key(renderer, x, y, c[0], 1);
            // SDL_Color color = { 0, 0, 0 };
            // draw_char(x+22, y+150, font, c, color, renderer);
        } else {
            draw_black_key(renderer, x, y, c[0], 0);
            // SDL_Color color = { 255, 255, 255 };
            // draw_char(x+22, y+150, font, c, color, renderer);
        }
    }


    SDL_RenderPresent(renderer);
    return 1;
}

// void draw_char(double dx, double dy, TTF_Font* font, char * c, SDL_Color color, SDL_Renderer* renderer) {
//     SDL_Surface* msg = TTF_RenderText_Solid(font, c, color);
//     SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, msg);
//     SDL_Rect r;
//     r.x = dx;
//     r.y = dy;
//     r.w = msg->w;
//     r.h = msg->h;
//     SDL_RenderCopy(renderer, Message, NULL, &r);
//     SDL_FreeSurface(msg);
//     SDL_DestroyTexture(Message);
// }

void kill_SDL(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    // TTF_Quit();
}

void draw_white_key(SDL_Renderer* renderer, double x, double y, char c, int pressed) {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = 100;
    r.h = 400;
    if(pressed) SDL_SetRenderDrawColor(renderer, 186, 219, 255, 255);
    else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &r);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &r);
}

void draw_black_key(SDL_Renderer* renderer, double x, double y, char c, int pressed) {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = 60;
    r.h = 250;
    if(pressed) SDL_SetRenderDrawColor(renderer, 186, 219, 255, 255);
    else SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &r);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &r);
}
