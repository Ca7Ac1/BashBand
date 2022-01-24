#ifndef SYNTH_H
#define SYNTH_H

// instruments avaliable:
// sine, square, triangle, sawtooth, trapezium, exp, [white]noise, tpdfnoise, pinknoise, brownnoise, pluck

typedef struct notes
{
    int pid;
    char instrument[15];
    char note[5];
    char id[100];
    struct notes *next;
} notes;

int play(char *instrument, char *note);
void stop(int pid);

notes *add_note(notes *n, char *instrument, char *note, char *id);
notes *remove_note(notes *n, char *id);
notes *free_notes(notes *n);

#endif
