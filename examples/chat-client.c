#include "easyTCP.h"
#include "chat.h"
#include <stdio.h>

#define BUFFER_SIZE 1024
#define PORT 8081

int main(void)
{
    int tmp;
    struct socketInfo server;
    char *buffer = "message from client";
    
    printf("sending buffer: %s\n", buffer);
    tmp = connectToServer(&server, "localhost", PORT);
    if (tmp < 0) return -1;
    setNonBlock(&server);

    sendMessage(&server, buffer, BUFFER_SIZE);

    // loop
    while(1)
    {
        recvMessage(&server, buffer, BUFFER_SIZE);
        printf("received: %s\n", buffer);
    }


    return 0;
}
