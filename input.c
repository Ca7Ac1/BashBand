#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include "log.h"
#include "synth.h"
#include "input.h"

void setup_notes() {
    // if(file == NULL) {
        printf("ok\n");
        //0: C, 1: C#, 2: D, 3: D#, 4: E, 5: F, 6: F#, 7: G, 8: G#, 9: A, 10: A#, 11: B
        key notes[12];
        notes[0].note[0] = 'C';
        notes[1].note[0] = 'C';
        notes[2].note[0] = 'D';
        notes[3].note[0] = 'D';
        notes[4].note[0] = 'E';
        notes[5].note[0] = 'F';
        notes[6].note[0] = 'F';
        notes[7].note[0] = 'G';
        notes[8].note[0] = 'G';
        notes[9].note[0] = 'A';
        notes[10].note[0] = 'A';
        notes[11].note[0] = 'B';
        for(int i = 0; i < 12; i++) {
            if(i==1||i==3||i==6||i==8||i==10) {
                notes[i].note[1] = '#';
            } else {
                notes[i].note[1] = '\0';
            }
            notes[i].note[2] = '\0';
            notes[i].note[3] = '\0';
            printf("%s\n", notes[i].note);
        }
    // }
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
