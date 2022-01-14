#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

#include "server.h"
#include "message.h"
#include "networking.h"
#include "log.h"

int main()
{
	server();
}

void server() 
{
	int server_socket = server_setup(SERVER_ADDR, SERVER_PORT);
	int connection_id = 0;

	connections *c;
	c = add_connections(c, server_socket, -1);
	while (1)
	{
		int rd = read_connections(c);
		
		if (rd == server_socket)
		{
			int new_connection = server_connect(server_socket);
			c = add_connections(c, new_connection, connection_id);
			
			write(c, &connection_id, sizeof(connection_id));

			connection_id++;
		}
		else
		{
			message msg; 
			int amt_read = read(rd, &msg, sizeof(msg));
			err_info(amt_read < sizeof(msg) ? -1 : 0, "checking if msg read is accurate");

			handle_message(msg);
		}
	}

	return 0;
}

void handle_message(message msg)
{

}