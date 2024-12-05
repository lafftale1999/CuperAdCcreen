#ifndef MESSAGES_H
#define MESSAGES_H

#include "config.h"
#include "message.h"

class Messages
{
    private:
        Message messages[MAX_MESSAGES];
        char messagesSize;

    public:
        Messages();
        void addMessage(Message message);
        Message& getMessage(int index);
        Message* getMessages();
        int getSize();
};

#endif