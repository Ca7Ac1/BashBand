#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>

#include "server.h"
#include "message.h"
#include "networking.h"
#include "log.h"

int main()
{
	setup_log(STDOUT_FILENO);
	server();
}

void server()
{
	int server_socket = server_setup(SERVER_ADDR, SERVER_PORT);
	connections *c = add_connection(NULL, server_socket);

	while (1)
	{
		int rd = read_connections(c);
		if (rd == server_socket)
		{
			int new_connection = server_connect(server_socket);
			c = add_connection(c, new_connection);

			write(new_connection, &new_connection, sizeof(new_connection));
		}
		else
		{
			message msg;
			int amt_read = read(rd, &msg, sizeof(message));

			if (amt_read < sizeof(message))
			{
				remove_connection(rd);
				msg.type = KICK_CONNECTION_MSG;
				write(rd, &msg, sizeof(message));

				//TODO: write that that connection disconnected
			}
			else
			{
				handle_message(msg);
			}
		}
	}
}

void handle_message(message msg)
{

}
