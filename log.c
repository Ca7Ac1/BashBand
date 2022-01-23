#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "log.h"

void setup_log(int descriptor)
{
    log_descriptor = descriptor;
}

void err(int e)
{
    if (e == -1)
    {
        char *err_des = "\nerrno: ";
        char *err_msg = strerror(errno);

        write(log_descriptor, err_des, sizeof(char) * strlen(err_des));
        write(log_descriptor, err_msg, sizeof(char) * strlen(err_msg));
        
        SDL_Quit();
        exit(-1);
    }
}

void err_info(int e, char *msg)
{
    char *msg_des = "\ninfo: ";

    write(log_descriptor, msg_des, sizeof(char) * strlen(msg_des));
    write(log_descriptor, msg, sizeof(char) * strlen(msg));

    if (e == -1)
    {
        char *err_des = "\nerrno: ";
        char *err_msg = strerror(errno);

        write(log_descriptor, err_des, sizeof(char) * strlen(err_des));
        write(log_descriptor, err_msg, sizeof(char) * strlen(err_msg));
        
        SDL_Quit();
        exit(-1);
    }
}

void info(char *msg)
{
    char *msg_des = "\ninfo: ";

    write(log_descriptor, msg_des, sizeof(char) * strlen(msg_des));
    write(log_descriptor, msg, sizeof(char) * strlen(msg));
}
