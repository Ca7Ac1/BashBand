#ifndef GUI_H
#define GUI_H

void init(SDL_Window *, SDL_Renderer *);

int loop(SDL_Window *, SDL_Renderer *);

void kill(SDL_Window *, SDL_Renderer *);

void draw_white_key(SDL_Renderer *, double, double);
void draw_black_key(SDL_Renderer *, double, double);

#endif