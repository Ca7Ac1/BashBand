#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "client.h"
#include "input.h"
#include "settings.h"
#include "gui.h"
#include "synth.h"
#include "message.h"
#include "networking.h"
#include "log.h"

// int main()
// {

//     setup_log(STDOUT_FILENO);

//     client(CLIENT_ADDR, CLIENT_PORT, "user");

//     return 0;
// }

void client(char *ip, char *port, char *name)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    init(&window, &renderer);
    
    TTF_Font *font;
    font=TTF_OpenFont("./fonts/OpenSans-Regular.ttf", 20);

    if(!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
    int client_socket;
    int id = open_connection(&client_socket, ip, port, name);

    key *keys = setup_notes(NULL);
    char *held = calloc(1, NOTES * sizeof(char));
    char settings = 'q';

    notes *n = NULL;
    char instrument[10] = "sin";

    while (1)
    {
        message *input_data = get_server_data(client_socket);

        if (input_data)
        {
            n = handle_client_message(n, client_socket, input_data);
            free(input_data);
        }

        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                int pressed = get_note_pressed(event, keys, settings);

                if (pressed == -1)
                {       
                    n = stop_all_notes(n, client_socket);
                    
                    for (int i = 0; i < NOTES; i++)
                    {
                        held[i] = 0;
                    }

                    loop(window, renderer, font, held);
                    alter_settings(&settings, instrument, &keys);
                }
                else if (pressed >= 0 && held[pressed] == 0)
                {
                    held[pressed] = 1;
                    n = play_input(n, client_socket, keys[pressed].note, instrument, id);
                }

                break;
            }
            else if (event.type == SDL_KEYUP)
            {
                int pressed = get_note_pressed(event, keys, settings);

                if (pressed >= 0)
                {
                    held[pressed] = 0;
                    n = stop_input(n, client_socket, keys[pressed].note, instrument, id);
                }

                break;
            }
            else if (event.type == SDL_QUIT)
            {
                kill_SDL(window, renderer);
                kill(-1 * getpid(), SIGKILL);

            }
        }

        loop(window, renderer, font, held);
    }
}

int open_connection(int *client_socket, char *ip, char *port, char *name)
{
    *client_socket = client_setup(ip, port);

    int id = -1;
    read(*client_socket, &id, sizeof(id));
    err(id);

    message open;
    open.type = OPEN_CONNECTION_MSG;
    open.data.open_data.id = id;
    strcpy(open.data.open_data.name, name);
    write(*client_socket, &open, sizeof(message));

    return id;
}

message *get_server_data(int client_socket)
{
    fd_set readfd;
    FD_ZERO(&readfd);
    FD_SET(client_socket, &readfd);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 5000;

    int max = client_socket + 1;

    
    int size = select(max, &readfd, NULL, NULL, &timeout);

    if (size == 1)
    {
        message *msg = malloc(sizeof(message));
        size = read(client_socket, msg, sizeof(message));

        err(size == sizeof(message) ? 1 : -1);

        return msg;
    }

    return NULL;
}

notes *handle_client_message(notes *n, int rd, message *msg)
{
    if (msg->type == KICK_CONNECTION_MSG)
    {
        printf("Host exited, or you lost connections\n");
        n = free_notes(n);
        exit(0);
    }
    else if (msg->type == OPEN_CONNECTION_MSG)
    {
        open_message *data = &msg->data.open_data;
        info("Client sees that another user connected");
        // printf("%s (id: %d) connected\n", data->name, data->id);
    }
    else if (msg->type == PLAY_NOTE_MSG)
    {
        note_message *data = &msg->data.note_data;
        n = add_note(n, data->instrument, data->note, data->note_id);
    }
    else if (msg->type == STOP_NOTE_MSG)
    {
        stop_message *data = &msg->data.stop_data;
        n = remove_note(n, data->note_id);
    }

    return n;
}