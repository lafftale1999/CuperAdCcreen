#include "../include/character.h"

Character::Character()
{
    for(int i = 0; i < MAX_BIT_BITMAP; i++)
    {
        this->bitMap[i] = 0;
    }
}
Character::Character(uint8_t bitMap[])
{
    for(int i = 0; i < MAX_BIT_BITMAP; i++)
    {
        this->bitMap[i] = bitMap[i];
    }
}

uint8_t* Character::getBitMap()
{
    return this->bitMap;
}