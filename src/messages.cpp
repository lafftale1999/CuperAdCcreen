#include "../include/messages.h"

#include "string.h"

Messages::Messages()
{
    this->messagesSize = 0;
}

void Messages::addMessage(Message message)
{
    this->messages[this->messagesSize++] = message;
}

Message Messages::getMessage(int index)
{
    return this->messages[index];
}

Message* Messages::getMessages()
{
    return this->messages;
}

int Messages::getSize()
{
    return this->messagesSize;
}