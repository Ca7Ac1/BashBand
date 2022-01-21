#ifndef INPUT_H
#define INPUT_H

#define NOTES 12

// this name is beautiful appreciate it pls
typedef struct key
{
    char button;
    // C#4 null
    char note[4];
} key;

key* setup_notes();
int input();

int isKeyDown(char);

#endif
