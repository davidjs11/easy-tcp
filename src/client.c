#include "easyTCP.h"

int main(void)
{
    int tmp;
    struct socketInfo server;
    char buffer[256];

    // connect to the server
    tmp = connectToServer(&server, "localhost", 8080);
    if (tmp < 0)
        return 0;

    // receive a message from server
    tmp = recvMessage(&server, buffer, 256);
    if (tmp < 0)
        return 0;

    printf("%d: %s\n", tmp, buffer);
    return 0;
}
