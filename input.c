#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

#include "log.h"
#include "synth.h"
#include "input.h"

key *setup_notes()
{
    // if(file == NULL) {
    // 0: C, 1: C#, 2: D, 3: D#, 4: E, 5: F, 6: F#, 7: G, 8: G#, 9: A, 10: A#, 11: B

    key *key_notes = malloc(sizeof(key) * NOTES);
    key_notes[0] = (key){.button = 'z', .note = "C"};
    key_notes[1] = (key){.button = 's', .note = "C#"};
    key_notes[2] = (key){.button = 'x', .note = "D"};
    key_notes[3] = (key){.button = 'd', .note = "D#"};
    key_notes[4] = (key){.button = 'c', .note = "E"};
    key_notes[5] = (key){.button = 'v', .note = "F"};
    key_notes[6] = (key){.button = 'g', .note = "F#"};
    key_notes[7] = (key){.button = 'b', .note = "G"};
    key_notes[8] = (key){.button = 'h', .note = "G#"};
    key_notes[9] = (key){.button = 'n', .note = "A"};
    key_notes[10] = (key){.button = 'j', .note = "A#"};
    key_notes[11] = (key){.button = 'm', .note = "B"};

    return key_notes;
}

int input()
{
    int pipe_des[2];
    pipe(pipe_des);

    int c = fork();
    err_info(c, "forking for input");

    if (c)
    {
        close(pipe_des[1]);
        return pipe_des[0];
    }

    close(pipe_des[0]);

    key *keys = setup_notes();

    initscr();

    cbreak();
    nodelay(stdscr, 1);
    noecho();

    while (1)
    {
        char c = getch();

        if (c != ERR)
        {
            printf("recieved: [%c]\n", c);
            refresh();
        }
    }
}
