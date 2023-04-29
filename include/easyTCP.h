#ifndef EASY_TCP
#define EASY_TCP

// standard libraries
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// socket libraries
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

// socket information structure
struct socketInfo 
{
    int socket, port;
    struct sockaddr_in address;
    int backlog;
    socklen_t length;
};

// server functions
int initServer(struct socketInfo *server, int port, int backlog);
void closeServer(struct socketInfo *server);
void acceptClient(struct socketInfo *server, struct socketInfo *client);

// client functions
int connectToServer(struct socketInfo *server, const char *ip, int port);
void disconnectFromServer(struct socketInfo *server);

// common functions
int sendMessage(struct socketInfo *to, char *buffer, int bufferSize);
int recvMessage(struct socketInfo *from, char *buffer, int bufferSize);


#endif
