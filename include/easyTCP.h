#ifndef EASY_TCP
#define EASY_TCP

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>

struct socketInfo 
{
    int socket, port;
    struct sockaddr_in address;
    int backlog;
};

// server functions
int initServer(struct socketInfo *server, int port, int backlog);
void closeServer(struct socketInfo *server);

// client functions
int connectToServer(struct socketInfo *server, const char *ip, int port);
void disconnectFromServer(struct socketInfo *server);

// common functions
int sendMessage(struct socketInfo *receiver, struct socketInfo *sender);
int recvMessage(struct socketInfo *receiver, struct socketInfo *sender);

#endif
