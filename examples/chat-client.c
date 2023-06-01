#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>

#define BUFFER_SIZE 256
#define MAX_MSG 30

int main() {
    char buffer[BUFFER_SIZE];

    char readBuffer[BUFFER_SIZE] = {0};
    int readChars = 0;

    char msgBuffer[MAX_MSG][BUFFER_SIZE] = {0};
    int updateScreen = 1;

    char ch; // temporal character

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);

    int y, x;
    getmaxyx(stdscr, y, x);  // Obtener dimensiones de la ventana

    // main loop
    while (1)
    {

        if ((ch = getch()) > 0)
        {
            if (ch == '\n')
            {
                // send buffer

                // put input into message buffer
                memmove(msgBuffer+(MAX_MSG-1), readBuffer, BUFFER_SIZE);

                // reset read buffer
                memset(readBuffer, 0, BUFFER_SIZE);
                readChars = 0;

                // delete last message
                memmove(msgBuffer, msgBuffer+1, BUFFER_SIZE*(MAX_MSG));
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
            mvprintw(y - 1, 0, "> ");  // Imprimir el prompt para la entrada del usuario
            updateScreen = 0;
        }

        move(y - 1, 2+readChars);
        refresh();

        //usleep(30000);
        
    }

    endwin();

    return 0;
}
