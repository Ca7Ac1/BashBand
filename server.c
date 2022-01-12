#include <stdlib.h>
#include <unistd.h>

#include "networking.h"
#include "log.h"

int main() 
{
    int fd[2];
    err_inf(pipe(fd), "creating pipes for server processes");

    int c = fork();
    err_inf(pipe(fd), "server forking");

    if (c)
    {
        close(fd[0]);

        //TODO: Create constants for ports and such
        int server_socket = server_setup("127.0.0.1", 9001);

        while (1)
        {
            int client = server_connect(server_socket);
            write(fd[1], &client, sizeof(client));
        }
    }
    else
    {
        close(fd[1]);

        while (1)
        {
            //TODO: select data from either parent process or connected clinets and handle logic
        }
    }

	return 0;
}