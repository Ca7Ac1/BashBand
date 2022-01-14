#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include "log.h"
#include "synth.h"
#include "input.h"

int main()
{
    setup_log(STDOUT_FILENO);
    int pid = 0;

    setup_notes();

    while (1)
    {
        input();
    }

    return 0;
}
