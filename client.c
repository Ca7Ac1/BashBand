#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

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

    int id = 999;
    read(client_socket, &id, sizeof(id));

    printf("%d connected\n", id);
}