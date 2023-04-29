# easyTCP
An easy-to-use TCP server/client library for C/C++.

## About
This project was made for a future Granada's GDSC talk about sockets and how to use them in C/C++. This library aims to be a simple and effective collection of functions that let beginner users implement client/server apps in C/C++ without struggling with original sys/socket.h functions and structures. Obviously this shouldn't be used in serious projects, where security is one of the main goals.

## How to compile
- Download this repository using ```git clone github.com/davidjs11/easy-tcp```.
- ```make``` will compile everything, both library and examples.
- ```make lib``` will compile the library. Just put the ```libeasyTCP.a``` and ```easyTCP.h``` files inside your project and you're ready to go!
- Don't forget to use ```-leasyTCP``` while compiling your program.

## Example list
- Echo client/server
- Simple HTTP server (only supports GET method)
- Message app (not done)

## Future ideas
- socket configuration functions
- better error handling
- other ways to transfer data 
- multiple connection handling (socket pools)
- user auth 

# How to use this library
This section doesn't aim to be a documentation (it will appear if the project grows), just an easy tutorial on how to use this library. We can find the following aspects:
## socketInfo structure
This structure contains data about a socket/address entity (either the current/remote server or a client). This structure contains fundamental data for the sockets to work, such as the file descriptor or the address, etc. But the user doesn't need to care about the data inside the structure.

## Server functions
### int initServer(struct socketInfo *server, int port, int backlog);
Inits the server on the indicated port and backlog, using the machine's IP address. It returns -1 in case of error and 0 if everything went correctly.
### void closeServer(struct socketInfo *server);
Closes the file descriptor and deletes the information in the socketInfo structure.
### void acceptClient(struct socketInfo *server, struct socketInfo *client);
Blocks the program until a new connection appears, and then saves the client info in the client socketInfo structure.

## Client functions
### int connecToServer(struct socketInfo *server, const char *ip, int port);
Starts a new connection to the indicated IPv4 address and port, and saves the server information in the server structure. It returns -1 in case of error and 0 if everything worked fine.
## void disconnectFromServer(struct socketInfo *server);
Closes the connection between client and server and deletes the server info from the structure.

## Common function
### int sendMessage(struct socketInfo *to, char *buffer, int bufferSize);
Sends the indicated buffer as a message to the "to" socket. It returns the number of bytes sent.
## int recvMessage(struct socketInfo *from, char *buffer, int bufferSize);
Receives data from a socket and saves it into the buffer. It returns the number of bytes received.



Feel free to send any feedback or pull request. I'd really appreciate if you send any project made with the library!
