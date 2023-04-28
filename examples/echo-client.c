#include "easyTCP.h"
#include <assert.h>
#define BUFFER_SIZE 256
#define PORT 8080

void getInput(char *buffer);

int main(void)
{
    int tmp;
    struct socketInfo server;
    char buffer[BUFFER_SIZE];

    // first message input
    printf("message:\t");
    getInput(buffer);

    while(strcmp(buffer, "0"))
    {
        // connect to the server
        tmp = connectToServer(&server, "localhost", PORT);
        assert(tmp);

        // send message to the server
        tmp = sendMessage(&server, buffer, BUFFER_SIZE);
        assert(tmp);
        printf("message sent to server.\n");

        // receive from the server
        tmp = recvMessage(&server, buffer, BUFFER_SIZE);
        assert(tmp);
        printf("message received: %s\n\n", buffer);

        // get next message from input
        printf("message:\t");
        getInput(buffer);
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
