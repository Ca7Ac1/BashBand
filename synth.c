#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#include "synth.h"
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
    err(kill(pid, SIGKILL));
}


notes *add_note(notes *n, char *instrument, char *note)
{
    notes *temp = malloc(sizeof(notes));
    
    strcpy(temp->note, note);
    strcpy(temp->instrument, instrument);
    temp->pid = play(instrument, note);
    temp->next = n;
    
    return temp;
}

notes *remove_note(notes *n, int pid)
{
    if (n && n->pid == pid)
    {
        stop(pid);

        notes *temp = n;
        n = n->next;
        free(temp);

        return n;
    }

    while (n->next)
    {
        if (n->next->pid == pid)
        {
            stop(pid);
            
            notes *temp = n->next;
            n->next = n->next->next;
            free(temp);

            return n;
        }

        n = n->next;
    }

    return n;
}

notes *free_notes(notes *n)
{
    while (n)
    {
        notes *temp = n;
        n = n-> next;
        free(temp);
    }

    return NULL;
}