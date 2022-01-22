#include <stdlib.h>
#include <stdio.h>
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
        char log_msg[100];
        sprintf(log_msg, "instrument: %s, note: %s", instrument, note);
        info(log_msg);

        char *cmd[] = {"play", "-qn", "synth", "100", instrument, note, NULL};
        execvp(cmd[0], cmd);

        err_info(-1, "execvp to play sound did not take over process");
    }
}

void stop(int pid)
{
    err(kill(pid, SIGKILL));
}

notes *add_note(notes *n, char *instrument, char *note, char *id)
{
    notes *temp = malloc(sizeof(notes));

    strcpy(temp->note, note);
    strcpy(temp->instrument, instrument);
    strcpy(temp->id, id);

    temp->pid = play(instrument, note);
    temp->next = n;

    return temp;
}

notes *remove_note(notes *n, char *id)
{
    if (!n)
    {
        return n;
    }

    if (strcmp(n->id, id) == 0)
    {
        stop(n->pid);

        notes *temp = n;
        n = n->next;
        free(temp);

        return n;
    }

    notes *head = n;
    while (n->next)
    {
        if (strcmp(n->next->id, id) == 0)
        {
            stop(n->next->pid);

            notes *temp = n->next;
            n->next = n->next->next;
            free(temp);

            return n;
        }

        n = n->next;
    }

    return head;
}

notes *free_notes(notes *n)
{
    while (n)
    {
        notes *temp = n;
        n = n->next;
        free(temp);
    }

    return NULL;
}
