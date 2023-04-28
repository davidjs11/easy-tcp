# easyTCP
An easy-to-use TCP server/client library for C/C++.

## About
This project was made for a future Granada's GDSC talk about sockets and how to use them in C/C++. My intention is to create a simple and effective collection of functions that let beginner users implement client/server apps in C/C++ without struggling with original sys/socket.h functions and structures. Obviously this shouldn't be used in serious projects, where security is one of the main goals.

## How to compile
- Download this repository using ```git clone github.com/davidjs11/easy-tcp```.
- Inside the easy-tcp/ folder, type ```make lib``` and it will compile the library only. Just grab the ```easyTCP.h``` and ```libeasyTCP.a``` files and you're ready to go.
- If you want to test the examples, write ```make``` and execute them (they're inside the ./bin folder).

## Example list
- Echo client/server




Feel free to send any feedback or pull request. I'd really appreciate if you send any project made with the library!
