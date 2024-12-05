#include "../include/message.h"
#include <string.h>

Message::Message()
{
    this->text[0] = '\0';
}

Message::Message(char text[], char effect[])
{
    setText(text);
    setEffect(effect);
}

void Message::setText(char text[MAX_STRING_LENGTH])
{
    this->text[0] = '\0';
    strcpy(this->text, text);
}

void Message::setEffect(char effect[])
{   
    if(!strcmp(effect, "scroll"))
    {
        this->effect = SCROLL;
    }

    else if(!strcmp(effect, "blink"))
    {
        this->effect = BLINK;
    }

    else if(!strcmp(effect, "plain"))
    {
        this->effect = PLAIN;
    }
}

char* Message::getText()
{
    return this->text;
}

Effect Message::getEffect()
{
    return this->effect;
}