#include "../include/characters.h"

CharactersFromPROGMEM init_characters()
{
    CharactersFromPROGMEM characters = 
    {
        {
            // BITMAP 1
            {
                "Heart",
                {
                0b00000,
                0b00000,
                0b01010,
                0b10101,
                0b10101,
                0b01010,
                0b00100,
                0b00000
                }
            },

            // BITMAP 2
            {
                "House",
                {
                0b00000,
                0b00100,
                0b01110,
                0b11111,
                0b01110,
                0b01010,
                0b01110,
                0b01110
                }
            },

            // BITMAP 3
            {
                "Smiley",
                {
                0b00000,
                0b00000,
                0b01010,
                0b00000,
                0b10001,
                0b01110,
                0b00000,
                0b00000
                }
            },

            // BITMAP 4
            {
                "Logo",
                {
                0b11101,
                0b10000,
                0b11101,
                0b00000,
                0b10111,
                0b00101,
                0b10111,
                0b00101
                }
            }
        },
        CHAR_IN_LIST
    };

    return characters;
}

Character::Character(CharacterFromPROGMEM character)
{
    for(int i = 0; i < MAX_BIT_BITMAP; i++)
    {
        this->bitMap[i] = character.bitMap[i];
    }
}

uint8_t* Character::getBitMap()
{
    return this->bitMap;
}