#ifndef INPUT_H
#define INPUT_H

// this name is beautiful appreciate it pls
typedef struct key {
    char button;
    char note[4];
} key;

void setup_notes();

void input();

#endif
