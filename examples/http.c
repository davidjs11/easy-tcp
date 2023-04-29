///////////////////////////////
///  UNDER CONSTRUCTION     ///
///////////////////////////////

#include "easyTCP.h"
#include <assert.h>

#define BUFFER_SIZE 1024
#define PORT 8080

int main(void)
{
    int tmp;
    struct socketInfo server;
    struct socketInfo client;

    char request[BUFFER_SIZE];
    char filename[BUFFER_SIZE];

    char *header200 = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length ";
    char response[BUFFER_SIZE];

    tmp = initServer(&server, PORT, 5);

    strcpy(response, "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 14\n\ndimelo mansana");
    while(1)
    {
        acceptClient(&server, &client);
        recvMessage(&client, request, BUFFER_SIZE);

        printf("%s\n", request);
        
        sendMessage(&client, response, BUFFER_SIZE);
    }
}
