#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "client_test.h"
#include "gui.h"
#include "synth.h"
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
    set_client_defaults(ip, port, name);

    int client_socket;
    int id = open_connection(&client_socket, ip, port, name);

    SDL_Event event;

    key *keys = setup_notes();
    char *held = calloc(1, NOTES * sizeof(char));

    notes *n = NULL;
    char instrument[10] = "sin";

    while (1)
    {
        message *input_data = get_server_data();

        if (input_data)
        {
            n = handle_message(n, client_socket, input_data);
            free(input_data);
        }

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                int pressed = get_note_pressed(event, keys);

                if (pressed != -1 && held[pressed] == 0)
                {
                    held[pressed] = 1;
                    n = play_input(n, client_socket, keys[pressed].note, instrument, id);
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                int pressed = get_note_pressed(event, keys);

                if (pressed != -1)
                {
                    held[pressed] = 0;
                    n = stop_input(n, client_socket, keys[pressed].note, instrument, id);
                }
            }
            else if (event.type == SDL_QUIT)
            {
                // kill_SDL(window, renderer);
            }
        }
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

void set_client_defaults(char *ip, char *port, char *name)
{
    if (!ip)
    {
        strcpy(ip, CLIENT_ADDR);
    }

    if (!port)
    {
        strcpy(port, CLIENT_PORT);
    }

    if (!name)
    {
        strcpy(name, "USER");
    }
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

notes *handle_message(notes *n, int rd, message *msg)
{
    if (msg->type == KICK_CONNECTION_MSG)
    {
        printf("Host exited, or you were kicked\n");
        n = free_notes(n);
        exit(0);
    }
    else if (msg->type == OPEN_CONNECTION_MSG)
    {
        open_message *data = &msg->data.open_data;
        printf("%s (id: %d) connected\n", data->name, data->id);
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

key *setup_notes()
{
    // if(file == NULL) {
    // 0: C, 1: C#, 2: D, 3: D#, 4: E, 5: F, 6: F#, 7: G, 8: G#, 9: A, 10: A#, 11: B

    key *key_notes = malloc(sizeof(key) * NOTES);
    key_notes[0] = (key){.button = 'Z', .note = "C"};
    key_notes[1] = (key){.button = 'S', .note = "C#"};
    key_notes[2] = (key){.button = 'X', .note = "D"};
    key_notes[3] = (key){.button = 'D', .note = "D#"};
    key_notes[4] = (key){.button = 'C', .note = "E"};
    key_notes[5] = (key){.button = 'V', .note = "F"};
    key_notes[6] = (key){.button = 'G', .note = "F#"};
    key_notes[7] = (key){.button = 'B', .note = "G"};
    key_notes[8] = (key){.button = 'H', .note = "G#"};
    key_notes[9] = (key){.button = 'N', .note = "A"};
    key_notes[10] = (key){.button = 'J', .note = "A#"};
    key_notes[11] = (key){.button = 'M', .note = "B"};

    return key_notes;
}

int get_note_pressed(SDL_Event event, key *keys)
{
    SDL_KeyboardEvent *key = &event.key;
    char keystroke = SDL_GetKeyName(key->keysym.sym)[0];

    for (int i = 0; i < NOTES; i++)
    {
        if (keys[i].button == keystroke)
        {
            return i;
        }
    }

    return -1;
}

notes *play_input(notes *n, int client_socket, char *note, char *instrument, int id)
{
    char msg_id[25];
    sprintf(msg_id, "%d-%s-%s", id, instrument, note);

    n = remove_note(n, msg_id);

    message msg;
    msg.type = STOP_NOTE_MSG;

    stop_message *data = &msg.data.stop_data;
    strcpy(data->note_id, msg_id);

    write(client_socket, &msg, sizeof(message));

    return n;
}

notes *stop_input(notes *n, int client_socket, char *note, char *instrument, int id)
{
    char msg_id[25];
    sprintf(msg_id, "%d-%s-%s", id, instrument, note);

    n = remove_note(n, msg_id);

    message msg;
    msg.type = STOP_NOTE_MSG;

    stop_message *data = &msg.data.stop_data;
    strcpy(data->note_id, msg_id);

    write(client_socket, &msg, sizeof(message));

    return n;
}