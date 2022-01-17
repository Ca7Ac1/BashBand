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

    char msg_id[25];

    notes *n = NULL;

    while (1)
    {
        int rd = read_connections(c);
        msg_id[0] = '\0';

        if (rd == STDIN_FILENO)
        {
            // TODO: use input.c for handling getting keystrokes
            char *instrument = "pluck";
            char *note = "C";
            char type[2] = "\0\0";

            fgets(type, sizeof(type), stdin);

            sprintf(msg_id, "%d-%s-%s", id, instrument, note);

            if (type[0] == 'p')
            {
                n = add_note(n, "pluck", "C", msg_id);

                message msg;
                msg.type = PLAY_NOTE_MSG;

                note_message *data = &msg.data.note_data;
                strcpy(data->instrument, instrument);
                strcpy(data->note, note);
                strcpy(data->note_id, msg_id);

                write_connections(c, msg);
            }
            else if (type[0] == 's')
            {
                n = remove_note(n, msg_id);
                
                message msg;
                msg.type = STOP_NOTE_MSG;

                stop_message *data = &msg.data.stop_data;
                strcpy(data->note_id, msg_id);

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
                n = free_notes(n);
                exit(0);
            }
            else if (msg.type == OPEN_CONNECTION_MSG)
            {
                // connect_message *data = &msg.data.connect_data;
                printf("Another person connected\n");
            }
            else if (msg.type == PLAY_NOTE_MSG)
            {
                note_message *data = &msg.data.note_data;
                n = add_note(n, data->instrument, data->note, data->note_id);
            }
            else if (msg.type == STOP_NOTE_MSG)
            {
                stop_message *data = &msg.data.stop_data;
                n = remove_note(n, data->note_id);
            }
        }
    }
}
