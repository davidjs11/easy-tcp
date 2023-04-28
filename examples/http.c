//strcpy(buffer, "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!");

#include "easyTCP.h"
#include <assert.h>

#define BUFFER_SIZE 1024
#define PORT 8080

int main(void)
{
    int tmp;
    struct socketInfo server;
    struct socketInfo client;
    char buffer[BUFFER_SIZE];

    tmp = initServer(&server, PORT, 5);

    strcpy(buffer, "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 14\n\ndimelo mansana");
    while(1)
    {
        acceptClient(&server, &client);
        sendMessage(&client, buffer, BUFFER_SIZE);
    }
}
