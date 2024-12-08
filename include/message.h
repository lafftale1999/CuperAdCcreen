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
        Message(const char text[], char effect[]);
        
        void setText(const char text[MAX_STRING_LENGTH]);
        void setEffect(const char effect[]);

        const char* getText();
        Effect getEffect();
};

#endif