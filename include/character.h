#ifndef __CHARACTERS_H
#define __CHARACTERS_H

#include "config.h"

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

class Character
{
private:
    uint8_t bitMap[MAX_BIT_BITMAP];

public:
    Character();
    Character(uint8_t bitMap[]);
    uint8_t* getBitMap();
};
#endif