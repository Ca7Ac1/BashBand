#ifndef INPUT_H
#define INPUT_H

// this name is beautiful appreciate it pls
typedef struct key
{
    char button;
    // C#4 null
    char note[4];
} key;

#define NOTES 12


key* setup_notes();

void input(key* key_notes);

#endif
