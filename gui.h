#ifndef GUI_H
#define GUI_H

void init(SDL_Window **, SDL_Renderer **);

int loop(SDL_Window *, SDL_Renderer *, TTF_Font *, char *);

void kill_SDL(SDL_Window *, SDL_Renderer *);

void draw_white_key(SDL_Renderer *, double, double, char, int);
void draw_black_key(SDL_Renderer *, double, double, char, int);
void draw_char(double, double, TTF_Font *, char *, SDL_Color, SDL_Renderer *);

#endif
