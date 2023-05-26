#include "easyTCP.h"
#include "chat.h"
#include <stdio.h>

#define BUFFER_SIZE 1024
#define PORT 8080

void getInput(char *buffer);

int main(void)
{
    int tmp;
    struct socketInfo server;
    char *buffer = "message from client";
    
    tmp = connectToServer(&server, "localhost", PORT);
    if (tmp < 0) return -1;
    setNonBlock(&server);

        //sendMessage(&server, buffer, BUFFER_SIZE);
    printf("sending buffer: %s\n", buffer);

    // loop
    while(1)
    {
        recvMessage(&server, buffer, BUFFER_SIZE);
        printf("message: %s\n", buffer);

    }


    return 0;
}

void getInput(char *buffer)
{
    fgets(buffer, BUFFER_SIZE, stdin);
    for(int i=0; i<BUFFER_SIZE; i++)
        if (buffer[i] == '\n')
            buffer[i] = '\0';
}
