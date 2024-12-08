#ifndef __CHARACTERS_H
#define __CHARACTERS_H

#include "config.h"

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

typedef struct
{
    uint8_t bitName[MAX_BITMAP_NAME];
    char bitMap[MAX_BIT_BITMAP];
}CharacterFromPROGMEM;

typedef struct
{
    CharacterFromPROGMEM characters[4];
    int charactersInList;
} CharactersFromPROGMEM;

CharactersFromPROGMEM init_characters();

class Character
{
private:
    uint8_t bitMap[MAX_BIT_BITMAP];
    char bitName[MAX_BITMAP_NAME];

public:
    Character(CharacterFromPROGMEM character);
    uint8_t* getBitMap();
};
#endif