#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "input.h"
#include "gui.h"
#include "synth.h"
#include "bad_client.h"
#include "message.h"
#include "networking.h"
#include "log.h"

int main()
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    font = TTF_OpenFont("fonts/OpenSans-Regular.ttf", 24);
    init(&window, &renderer);

    setup_log(STDOUT_FILENO);
    
    client(NULL, NULL, NULL);

    return 0;
}

void client(char *ip, char *port, char *name)
{
    int client_socket = client_setup(CLIENT_ADDR, CLIENT_PORT);
    int input_fd = input();

    connections *c = add_connection(NULL, client_socket);
    c = add_connection(c, input_fd);
    set_connection(c, input_fd, 1, 0);

    int id = -1;
    read(client_socket, &id, sizeof(id));
    err(id);

    message open;
    open.type = OPEN_CONNECTION_MSG;
    open.data.open_data.id = id;
    strcpy(open.data.open_data.name, "USER");
    write(client_socket, &open, sizeof(message));

    char msg_id[25];

    notes *n = NULL;

    while (1)
    {
        int rd = read_connections(c);
        msg_id[0] = '\0';

        if (rd == input_fd)
        {
            note_message input_data;
            int amt_read = read(rd, &input_data, sizeof(note_message));

            err(amt_read < sizeof(note_message) ? -1 : 1);

            sprintf(msg_id, "%d-%s-%s", id, input_data.instrument, input_data.note);

            if (input_data.note_id[0] == 'p')
            {
                n = add_note(n, input_data.instrument, input_data.note, msg_id);

                message msg;
                msg.type = PLAY_NOTE_MSG;

                note_message *data = &msg.data.note_data;
                strcpy(data->instrument, input_data.instrument);
                strcpy(data->note, input_data.note);
                strcpy(data->note_id, msg_id);

                write_connections(c, msg);
            }
            else if (input_data.note_id[0] == 's')
            {
                n = remove_note(n, msg_id);
                
                message msg;
                msg.type = STOP_NOTE_MSG;

                stop_message *data = &msg.data.stop_data;
                strcpy(data->note_id, msg_id);

                write_connections(c, msg);
            }
            else
            {
                err_info(-1, "bad input message recieved");
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
                open_message data = msg.data.open_data;
                printf("%s (id: %d) connected\n", data.name, data.id);
            }
            else if (msg.type == PLAY_NOTE_MSG)
            {
                note_message *data = &msg.data.note_data;
                n = add_note(n, data->instrument, data->note, data->note_id);
            }
            else if (msg.type == STOP_NOTE_MSG)
            {
                stop_message data = msg.data.stop_data;
                n = remove_note(n, data.note_id);
            }
        }
    }
}
