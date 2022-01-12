#include <unistd.h>
#include <string.h>
#include <errno.h>

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

        write(err_descriptor, err_des, sizeof(char) * strlen(err_des));
        write(err_descriptor, err_msg, sizeof(char) * strlen(err_msg));
    }
}

void err_info(int e, char *msg)
{    
    if (e == -1)
    {
        char *msg_des = "\ninfo: ";
        char *err_des = "\nerrno: ";
        char *err_msg = strerror(errno);

        write(err_descriptor, msg_des, sizeof(char) * strlen(msg_des));
        write(err_descriptor, msg, sizeof(char) * strlen(msg));
        write(err_descriptor, err_des, sizeof(char) * strlen(err_des));
        write(err_descriptor, err_msg, sizeof(char) * strlen(err_msg));
        
        exit(-1);
    }
}

void info(char *msg)
{
    write(err_descriptor, msg, sizeof(char) * strlen(msg));
}