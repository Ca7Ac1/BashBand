#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include "log.h"
#include "synth.h"

int main()
{
    setup_log(STDOUT_FILENO);
    int pid = 0;

    while (1)
    {
        char c[2] = "\0\0";

        fgets(c, sizeof(c), stdin);

        if (c[0] == 'p')
        {
            printf("play\n");
            pid = play("sine", "C");
        }
        else if (c[0] == 's')
        {
            printf("%d, stop\n", pid);
            stop(pid);
        }

        c[0] = 'u';
    }

    return 0;
}
