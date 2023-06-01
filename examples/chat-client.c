#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>
#include "easyTCP.h"

#define BUFFER_SIZE 256
#define MAX_MSG 30
#define PORT 8080

int main() {
    // input buffer
    char readBuffer[BUFFER_SIZE] = {0};
    int readChars = 0;
    char ch; // temporal character

    // receive buffer
    char recvBuffer[BUFFER_SIZE] = {0};
    int newMessage = 0;

    // message buffer
    char msgBuffer[MAX_MSG][BUFFER_SIZE] = {0};
    int updateScreen = 1;

    int tmp;
    struct socketInfo server;
    
    if(connectToServer(&server, "192.168.1.144", PORT) < 0)
        return -1;

    setNonBlock(&server);

    //sendMessage(&server, buffer, BUFFER_SIZE);


    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);

    int y, x;
    getmaxyx(stdscr, y, x);  // Obtener dimensiones de la ventana

    // main loop
    while (1)
    {

        if (newMessage)
        {

            // delete last message
            memmove(msgBuffer, msgBuffer+1, BUFFER_SIZE*(MAX_MSG-1));

            // put input into message buffer
            memmove(msgBuffer+(MAX_MSG-1), recvBuffer, BUFFER_SIZE);

            updateScreen = 1;
        }

        if ((ch = getch()) > 0)
        {
            if (ch == '\n')
            {
                // send buffer
                sendMessage(&server, readBuffer, BUFFER_SIZE);

                // reset read buffer
                memset(readBuffer, 0, BUFFER_SIZE);
                readChars = 0;
            }
            else if (ch == 127)
            {
                // delete last character
                readBuffer[readChars-1] = 0;
                readChars-=(readChars > 0);
            }
            else // add character
            {
                readBuffer[readChars] = ch;
                readChars++;
            }

            updateScreen = 1;
        }

        mvprintw(y - 1, 2, "%s", readBuffer);

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

        move(y - 1, 2+readChars);
        refresh();

        recvMessage(&server, recvBuffer, BUFFER_SIZE);
        newMessage = (recvBuffer[0]);
    }

    endwin();

    return 0;
}
