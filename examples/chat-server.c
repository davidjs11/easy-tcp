#include "easyTCP.h"
#include "chat.h"
#include <stdio.h>
#include <sys/select.h>
#include <signal.h>

#define BUFFER_SIZE 1024
#define PORT 8080
#define MAX_USERS 5

int main(void)
{
    int tmp;
    struct socketInfo server;
    struct socketInfo client[MAX_USERS];
    int connected = 0;
    char buffer[BUFFER_SIZE];

    // clear buffer
    for(int i=0; i<BUFFER_SIZE; i++) buffer[i] = 0;

    if (initServer(&server, PORT, 1) < 0) return -1;
    setNonBlock(&server);


    fd_set acceptedClients, readableClients;
    FD_ZERO(&acceptedClients);
    FD_SET(server.socket, &acceptedClients);

    while(1)
    {
        readableClients = acceptedClients;
        select(1024, &readableClients, NULL, NULL, NULL);

        if (FD_ISSET(server.socket, &readableClients))
        {
            acceptClient(&server, &client[connected]);
            FD_SET(client[connected].socket, &acceptedClients);
            setNonBlock(&client[connected]);
            connected++;
        }

        printf("connected: %d\n", connected);

        for(int i=0; i<connected; i++)
        {
            if (FD_ISSET(client[i].socket, &readableClients))
            {
                recvMessage(&client[i], buffer, BUFFER_SIZE);
                printf("message: %s\n", buffer);
                for(int j=0; j<connected; j++)
                    sendMessage(&client[j], buffer, BUFFER_SIZE);
            }
        }
    }



    return 0;
}
