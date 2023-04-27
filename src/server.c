#include "easyTCP.h"
#include <stdio.h>

int main(void)
{
    struct socketInfo server;
    initServer(&server, 8080, 4);
    printf("listening...\n");

    while (1)
    {
        printf("running!!\n");
    }

    return 0;
}
