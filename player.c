#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "player.h"
#include "log.h"

int play(char *instrument, char *note)
{
    int c = fork();
    err_info(c, "Forking to play sound");

    if (c)
    {
        return c;
    }
    else
    {
        char *cmd[] = {"play", "-qn", "synth", "100", instrument, note, NULL};
        execvp(cmd[0], cmd);

        err_info(-1, "execvp to play sound did not take over process");
    }
}

void stop(int pid)
{
    kill(pid, SIGKILL);
}