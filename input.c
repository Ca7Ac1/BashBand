#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include "log.h"
#include "synth.h"
#include "input.h"

key* setup_notes()
{
    // if(file == NULL) {
    printf("ok\n");
    // 0: C, 1: C#, 2: D, 3: D#, 4: E, 5: F, 6: F#, 7: G, 8: G#, 9: A, 10: A#, 11: B

    
    static key key_notes[] = {
        {.button = 'z',.note = "C"},
        {.button = 's',.note = "C"},
        {.button = 'x',.note = "C"},
        {.button = 'd',.note = "C"},
        {.button = 'c',.note = "C"},
        {.button = 'v',.note = "C"},
        {.button = 'g',.note = "C"},
        {.button = 'b',.note = "C"},
        {.button = 'h',.note = "C"},
        {.button = 'n',.note = "C"},
        {.button = 'j',.note = "C"},
        {.button = 'm',.note = "C"},
    };

    // notes[0].button = 'z';
    // notes[1].button = 's';
    // notes[2].button = 'x';
    // notes[3].button = 'd';
    // notes[4].button = 'c';
    // notes[5].button = 'v';
    // notes[6].button = 'g';
    // notes[7].button = 'b';
    // notes[8].button = 'h';
    // notes[9].button = 'n';
    // notes[10].button = 'j';
    // notes[11].button = 'm';
    
    // notes[0].note[0] = 'C';
    // notes[1].note[0] = 'C';
    // notes[2].note[0] = 'D';
    // notes[3].note[0] = 'D';
    // notes[4].note[0] = 'E';
    // notes[5].note[0] = 'F';
    // notes[6].note[0] = 'F';
    // notes[7].note[0] = 'G';
    // notes[8].note[0] = 'G';
    // notes[9].note[0] = 'A';
    // notes[10].note[0] = 'A';
    // notes[11].note[0] = 'B';

    // for (int i = 0; i < NOTES; i++)
    // {
    //     int j = i%12;
    //     if (j == 1 || j == 3 || j == 6 || j == 8 || j == 10)
    //     {
    //         buttons[i].note[1] = '#';
    //     }
    //     else
    //     {
    //         buttons[i].note[1] = '\0';
    //     }

    //     buttons[i].note[2] = '\0';
    //     buttons[i].note[3] = '\0';
    //     printf("%s\n", buttons[i].note);
    // }
    // }
    return key_notes;
}

static int pids[3];

void input(key* key_notes)
{
    char c[2] = "\0\0";

    fgets(c, sizeof(c), stdin);
    int i = 0;
    for(i = 0; i < NOTES; i++) {
        // printf("%d\n",i);
        // printf("%c\n", key_notes[i].button);
        if(c[0] == key_notes[i].button) {
            printf("play\n");
            play("pluck", key_notes[i].note);
        }
    }

    // if (c[0] == 'p')
    // {
    //     printf("play\n");
    //     pids[0] = play("pluck", "C");
    //     pids[1] = play("pluck", "E");
    //     pids[2] = play("pluck", "G");
    // }

    // if (c[0] == 's')
    // {
    //     printf("stop\n");
    //     stop(pids[0]);
    //     stop(pids[1]);
    //     stop(pids[2]);
    // }
}

/* promising input code. Would need to use a pipe and seperate process,
   but removes the need for external library to capture key event

    #include <ncurses.h>

    int main()
    {
        char c;
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);

        while('q' != (c = getch()))
        {
            printw("%c\n", c);
            if(halfdelay(5) != ERR)
            {
                while(getch() == c)
                {
                    if(halfdelay(1) == ERR) break;
                }
            }

            printw("Here\n");
            cbreak();
        }

        endwin();
        return 0;
    }
 */