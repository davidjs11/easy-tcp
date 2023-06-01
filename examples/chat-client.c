#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>
#include "easyTCP.h"

#define BUFFER_SIZE 256
#define USER_SIZE 12
#define MAX_MSG 30
#define PORT 8080

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("no username as argument\n");
        exit(1);
    }
    // input buffer
    char readBuffer[BUFFER_SIZE] = {0};
    int readChars = 0;
    char ch; // temporal character

    // username
    char username[USER_SIZE]; 
    strcpy(username, argv[1]);

    // receive and send buffers
    char recvBuffer[BUFFER_SIZE+USER_SIZE+2] = {0};
    char sendBuffer[BUFFER_SIZE+USER_SIZE+2] = {0};
    int newMessage = 0;

    // message buffer
    char msgBuffer[MAX_MSG][BUFFER_SIZE+USER_SIZE+2] = {0};
    int updateScreen = 1;

    // connect to server
    int tmp;
    struct socketInfo server;
    if(connectToServer(&server, "192.168.1.144", PORT) < 0)
        return -1;
    setNonBlock(&server);

    // ncurses stuff
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    int y, x;
    getmaxyx(stdscr, y, x); // screen dimensions 

    // main loop
    while (1)
    {
        if (newMessage)
        {
            // delete last message
            memmove(msgBuffer, msgBuffer+1, (BUFFER_SIZE+USER_SIZE+2)*(MAX_MSG-1));

            // put input into message buffer
            memmove(msgBuffer+(MAX_MSG-1), recvBuffer, BUFFER_SIZE+USER_SIZE+2);

            updateScreen = 1;
        }

        if ((ch = getch()) > 0)
        {
            if (ch == '\n')
            {
                // send buffer
                sprintf(sendBuffer, "%s: %s", username, readBuffer);
                sendMessage(&server, sendBuffer, BUFFER_SIZE+USER_SIZE+2);

                // reset read buffer
                memset(readBuffer, 0, BUFFER_SIZE);
                memset(sendBuffer, 0, BUFFER_SIZE+USER_SIZE+2);
                readChars = 0;
            }
            else if (ch == 127)
            {
                // delete last character
                readBuffer[readChars-1] = 0;
                readChars-=(readChars > 0);
            }
            else
            {
                // add character
                readBuffer[readChars] = ch;
                readChars++;
            }

            updateScreen = 1;
        }

        // print input
        mvprintw(y - 1, 2, "%s", readBuffer);

        // print messages
        for(int i=0; i<MAX_MSG; i++)
            mvprintw(i, 0, "%s",  msgBuffer[i]);

        if (updateScreen)
        {
            refresh();
            clear();
            mvprintw(0, x-5, "%d", newMessage);  // Imprimir el prompt para la entrada del usuario
            mvprintw(y - 1, 0, "> ");  // Imprimir el prompt para la entrada del usuario
            updateScreen = 0;
        }

        // update cursor position
        move(y - 1, 2+readChars);
        refresh();

        // receive messages from server
        recvMessage(&server, recvBuffer, BUFFER_SIZE+USER_SIZE+2+USER_SIZE+2);
        newMessage = (recvBuffer[0]);
    }

    endwin();

    return 0;
}
