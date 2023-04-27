#include "easyTCP.h"
#include <stdio.h>

int main(void)
{
    struct serverStruct server;
    initServer(&server);
    printf("%d\n", server.socket);



    return 0;
}
