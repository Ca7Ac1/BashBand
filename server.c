#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

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
	connections *c = add_connection(NULL, server_socket, -1);
	
	while (1)
	{	
		int rd = read_connections(c);

		if (rd == server_socket)
		{
			int new_connection = server_connect(server_socket);
			c = add_connection(c, new_connection, new_connection);
			
			write(new_connection, &new_connection, sizeof(new_connection));
		}
		else
		{
			message msg; 
			int amt_read = read(rd, &msg, sizeof(msg));
			err_info(amt_read < sizeof(msg) ? -1 : 0, "checking if msg read is accurate");

			handle_message(msg);
		}
	}
}

void handle_message(message msg)
{

}