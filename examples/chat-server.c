#include "easyTCP.h"
#include "chat.h"
#include <stdio.h>
#include <sys/select.h>

#define BUFFER_SIZE 1024
#define PORT 8081
#define MAX_USERS 5

int main(void)
{
    int tmp;
    struct socketInfo server;
    struct socketInfo client[MAX_USERS];
    int connected = 0;
    char buffer[BUFFER_SIZE];


    // clear buffer
    for(int i=0; i<BUFFER_SIZE; i++)
        buffer[i] = 0;

    tmp = initServer(&server, PORT, 1);
    if (tmp < 0) return -1;
    setNonBlock(&server);

    while(1)
    {
        if (connected < MAX_USERS)
            acceptClient(&server, &client[connected]);

        if (client[connected].socket > 0)
            connected++;

        /*
        for (int i=0; i<MAX_USERS; i++)
            printf("%d - ", client[i].socket);
        printf("\t%d\n", connected);
        */

        for(int i=0; i<connected; i++)
        {
            recvMessage(&client[i], buffer, BUFFER_SIZE);

            if (buffer[0] != 0)
            {
                printf("[%d] buffer: %s\n", i, buffer);
                printf("\n");
            }
                
            buffer[0] = 0;
        }



    }



    return 0;
}
