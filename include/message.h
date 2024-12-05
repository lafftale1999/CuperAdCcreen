#ifndef MESSAGE_H
#define MESSAGE_H

#include "config.h"

typedef enum
{
    BLINK,
    SCROLL,
    PLAIN
} Effect;

class Message
{
    private:
        char text[MAX_STRING_LENGTH];
        Effect effect;

    public:
        Message();
        Message(char text[], char effect[]);
        
        void setText(char text[MAX_STRING_LENGTH]);
        void setEffect(char effect[]);

        char* getText();
        Effect getEffect();
};

#endif