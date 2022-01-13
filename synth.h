#ifndef PLAYER_H
#define PLAYER_H

// instruments avaliable:
// sine, square, triangle, sawtooth, trapezium, exp, [white]noise, tpdfnoise, pinknoise, brownnoise, pluck

int play(char *instrument, char *note);
void stop(int pid);

#endif
