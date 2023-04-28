#include "easyTCP.h"
#define BUFFER_SIZE 256

int main(void)
{
    int tmp;
    struct socketInfo server;
    struct socketInfo client;
    char buffer[BUFFER_SIZE];

    tmp = initServer(&server, 8080, 5);
    if (tmp < 0)
        return -1;
    
    while(1)
    {
        client.socket = accept(server.socket,
                        (struct sockaddr *) &(client.address),
                        &(client.length));

        tmp = recvMessage(&client, buffer, BUFFER_SIZE);
        printf("received -> %d: %s\n", tmp, buffer);

        tmp = sendMessage(&client, buffer, BUFFER_SIZE);
        printf("message sent to the client.\n");
    }

    return 0;
}
