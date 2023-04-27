#include "easyTCP.h"

int initServer(struct socketInfo *server)
{
    int tmp; // temporal values for error handling

    // create socket file descriptor
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (!server->socket)
    {
        perror("[-] initServer() in socket()");
        return -1;
    }

    // config server address
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_family = AF_INET;
    server->address.sin_port = htons(server->port);

    // bind address to the socket
    tmp = bind(server->socket, (struct sockaddr *) &(server->address),
               sizeof(server->address));
    if (tmp < 0)
    {
        perror("[-] initServer() in bind()");
        return -1;
    }

    // start listening for new connections
    tmp = listen(server->socket, server->backlog+(!server->backlog));
    if (tmp < 0)
    {
        perror("[-] initServer() in listen()");
        return -1;
    }
}

void closeServer(struct socketInfo *server)
{
    // close socket
    close(server->socket);
    server->socket = 0;

    // delete address info
    server->address.sin_addr.s_addr = 0;
    server->address.sin_family = 0;
    server->address.sin_port = 0;
}
