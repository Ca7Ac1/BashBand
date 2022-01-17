#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>

#include "synth.h"
#include "client.h"
#include "message.h"
#include "networking.h"
#include "log.h"

int main()
{
    setup_log(STDOUT_FILENO);
    client();
}

void client()
{
    int client_socket = client_setup(CLIENT_ADDR, CLIENT_PORT);

    connections *c = add_connection(NULL, client_socket);
    c = add_connection(c, STDIN_FILENO);
    set_connection(c, STDIN_FILENO, 1, 0);

    int id = -1;
    read(client_socket, &id, sizeof(id));
    err(id);

    char msg_id[100];

    int pid;

    while (1)
    {
        int rd = read_connections(c);
        msg_id[0] = '\0';

        if (rd == STDIN_FILENO)
        {
            // TODO: use input.c for handling getting keystrokes
            char read_input[2] = "\0\0";

            fgets(read_input, sizeof(read_input), stdin);

            if (read_input[0] == 'p')
            {
                pid = play("pluck", "C");

                message msg;
                msg.type = PLAY_NOTE_MSG;

                note_message *data = &msg.data.note_data;
                strcpy(data->instrument, "pluck");
                strcpy(data->note, "C");

                sprintf(msg_id, "%d%s%s", id, "pluck", "C");
                strcpy(data->note_id, "");

                write_connections(c, msg);
            }
            else if (read_input[0] == 's')
            {
                stop(pid);

                message msg;
                msg.type = STOP_NOTE_MSG;

                stop_message *data = &msg.data.stop_data;

                sprintf(msg_id, "%d%s%s", id, "pluck", "C");
                strcpy(data->note_id, "");

                write_connections(c, msg);
            }
        }
        else if (rd == client_socket)
        {
            message msg;

            int amt_read = read(rd, &msg, sizeof(message));
            err(amt_read == sizeof(message) ? 1 : -1);

            if (msg.type == KICK_CONNECTION_MSG)
            {
                printf("Host exited, or you were kicked\n");
                exit(0);
            }
            else if (msg.type == OPEN_CONNECTION_MSG)
            {
                printf("Another person connected\n");
            }
            else if (msg.type == PLAY_NOTE_MSG)
            {
                pid = play("pluck", "C");
            }
            else if (msg.type == STOP_NOTE_MSG)
            {
                stop(pid);
            }
        }
    }
}
