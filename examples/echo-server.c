#include "easyTCP.h"
#include <stdio.h>
#define BUFFER_SIZE 2048
#define PORT 8081

int main(void)
{
    int tmp;
    struct socketInfo server;
    struct socketInfo client;
    char buffer[BUFFER_SIZE];

    tmp = initServer(&server, PORT, 5);
    if (tmp < 0)
        return -1;
    
    while(1)
    {
        acceptClient(&server, &client);

        tmp = recvMessage(&client, buffer, BUFFER_SIZE);
        printf("received -> %d: %s\n", tmp, buffer);

        tmp = sendMessage(&client, buffer, BUFFER_SIZE);
        printf("message sent to the client.\n");
    }

    return 0;
}
