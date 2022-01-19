#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include "log.h"
#include "synth.h"
#include "input.h"

int main()
{
    input();

    while (1) {}
    // setup_log(STDOUT_FILENO);
    // int pid = 0;

    // key *notes = setup_notes();

    // // printf("%s\n", notes);

    // while (1)
    // {
    //     input(notes);
    // }

    // return 0;
}
