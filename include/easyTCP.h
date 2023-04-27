#ifndef EASY_TCP
#define EASY_TCP

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

struct serverStruct 
{
    int socket, port;
    struct sockaddr_in address;
    int backlog;
};

// server functions
int initServer(struct serverStruct *server);

#endif
