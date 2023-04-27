#include "easyTCP.h"

int main(void)
{
    struct socketInfo server;

    int tmp = connectToServer(&server, "localhost", 8080);

    if (tmp > 0)
        printf("it works!!\n");
    return 0;
}
