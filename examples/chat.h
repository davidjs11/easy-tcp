#ifndef CHAT_H
#define CHAT_H

typedef struct
{
    char username[12+1];
    char password[32];
    int socket;

} userInfo;

#endif
