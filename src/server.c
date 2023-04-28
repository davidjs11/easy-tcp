#include "easyTCP.h"

int main(void)
{
    int tmp;
    struct socketInfo server;
    struct socketInfo client;

    // init the message buffer
    char buffer[256];
    strcpy(buffer, "message from server");

    // init server
    initServer(&server, 8080, 4);
    printf("listening...\n");

    while (1)
    {
        // wait for a client to connect
        client.socket = accept(server.socket,
                        (struct sockaddr *) &(client.address),
                        &(client.length));

        // handle a new connection
        printf("new connection!\n");
        tmp = sendMessage(&client, buffer, 256);
        printf("%d characters sent.\n", tmp);
    }

    return 0;
}
