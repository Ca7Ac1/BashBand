#ifndef PLAYER_H
#define PLAYER_H

// instruments avaliable:
// sine, square, triangle, sawtooth, trapezium, exp, [white]noise, tpdfnoise, pinknoise, brownnoise, pluck

typedef struct notes
{
    int pid;
    char *instrument;
    char *note;
    struct notes *next;
} notes;

int play(char *instrument, char *note);
void stop(int pid);

notes *add_note(notes *n, char *instrument, char *note);
notes *remove_note(notes *n, int pid);
notes *free_notes(notes *n);

#endif
