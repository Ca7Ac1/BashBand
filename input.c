#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include "log.h"
#include "player.h"

void setup_notes(char *file) {
    if(file == NULL) {
        key notes[12];
        //for(int i = 0; i < 12; i++) notes[i].note[];
    }
}

void input() {
    char c[2] = "\0\0";

    fgets(c, sizeof(c), stdin);

    if (c[0] == 'p')
    {
        printf("play\n");
        play("pluck", "C");
    }
}
