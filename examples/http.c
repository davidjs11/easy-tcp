/////////////////////////////////////////
///  THIS HTTP SERVER ONLY SUPPORTS   ///
///  GET METHODS. THIS IS AN EXAMPLE  ///
///  FOR THE EASYTCP LIBRARY          ///
/////////////////////////////////////////

#include "easyTCP.h"
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024
#define PORT 8081

// http request information (for GET method)
struct httpRequest
{
    char *method, *path, *version;
    int file;
    struct stat fileStat;
};

// extracts the information from a GET request header
void processRequest(char *buffer, struct httpRequest *request)
{
    request->method = strtok(buffer, " ");
    request->path = strtok(NULL, " ");
    request->version = strtok(NULL, "\r\n");
}

// sends the header to the client
void sendHeader(struct socketInfo *client,
                const char *ContentType, int ContentLength)
{
    // create the header
    char header[1024];
    snprintf(header, sizeof(header),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: %s\r\n"
             "Content-Length: %d\r\n"
             "\r\n",
             ContentType, ContentLength);

    // send the header
    sendMessage(client, header, strlen(header));
}

void sendFile(struct socketInfo *client,
              struct httpRequest *request)
{
    char buffer[BUFFER_SIZE];

    // open the requested file
    printf("%s\n", request->path+1);
    if ((request->file = open(request->path+1, O_RDONLY)) < 0)
    {
        printf("file not found :(\n");
        return;
    }

    // get file size
    fstat(request->file, &(request->fileStat));

    // send the header
    sendHeader(client, "text/html", request->fileStat.st_size);

    // send the file
    int n = 0;
    while((n = read(request->file, buffer, BUFFER_SIZE)) > 0)
        sendMessage(client, buffer, BUFFER_SIZE);
}

int main(void)
{
    int tmp;
    struct socketInfo server;
    struct socketInfo client;
    struct httpRequest request;

    char buffer[BUFFER_SIZE];

    // init the http server
    tmp = initServer(&server, PORT, 1);
    if (tmp < 0)
        return -1;

    while(1)
    {
        // accept connection and receive the request
        acceptClient(&server, &client);
        recvMessage(&client, buffer, BUFFER_SIZE);
        printf("new request! ");

        // get data from the request
        processRequest(buffer, &request);

        // send the file as response
        sendFile(&client, &request);
        printf("\n");
    }
}
