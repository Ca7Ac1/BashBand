#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "log.h"
#include "server.h"
#include "client.h"

void configure_client()
{
    char ip[20];
    char port[10];
    char name[100];

    char *ip_ptr = ip;
    char *port_ptr = port;
    char *name_ptr = name;
    
    printf("Enter ip address (format: 123.456.789.101) or hostname or leave blank for default (default: %s): ", CLIENT_ADDR);
    fgets(ip, sizeof(ip), stdin);


    printf("Enter port or leave blank for default (default: %s): ", CLIENT_PORT);
    fgets(port, sizeof(port), stdin);

    printf("Enter user name or leave blank for default: ");
    fgets(name, sizeof(name), stdin);

    ip_ptr = strsep(&ip_ptr, "\n");
    port_ptr = strsep(&port_ptr, "\n");
    name_ptr = strsep(&name_ptr, "\n");

    if (strlen(ip_ptr) < 7)
    {
        strcpy(ip_ptr, CLIENT_ADDR);
    }

    if (strlen(port_ptr) < 7)
    {
        strcpy(port_ptr, CLIENT_PORT);
    }

    if (strlen(name_ptr) < 7)
    {
        strcpy(name_ptr, "User");
    }

    client(ip_ptr, port_ptr, name_ptr);
}

int main()
{
    int log_file = open("log_file.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    setup_log(log_file);

    printf("BASH BAND\n\n");
    printf("This is an interactive multi-user online synth/keyboard created by Ayan Chowdhury and Wilde Chu\n");
    printf("Please enter what you would like to do:\n\n");

    while (1)
    {
        printf("1: Start server\n2: Start server and join yourself\n3: Join server\n");

        char input[100];
        fgets(input, sizeof(input), stdin);

        if (input[0] == '1')
        {
            server();
        }
        else if (input[0] == '2')
        {
            int c = fork();

            if (c)
            {
                server();
            }
            else
            {
                configure_client();
            }

            break;
        }
        else if (input[0] == '3')
        {
            configure_client();
            break;
        }
        else 
        {
            printf("invalid input, please try again\n\n");
        }
    }

    return 0;
}