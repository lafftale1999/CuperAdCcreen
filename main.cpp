#include "include/adChooser.h"
#include "include/lcd.h"
#include "include/utils.h"

#include <avr/pgmspace.h>
#include <stdio.h>

int main()
{   
    // creating and setting screen
    HD44780 screen;
    screen.Initialize();
    screen.Clear();

    // loading companies into PROGMEM
    const CompaniesPROGMEM companies PROGMEM = init_companies();

    // loading characters into PROGMEM
    const CharactersFromPROGMEM characters PROGMEM = init_characters();

    // creating adchooser
    AdChooser adChooser;

    // seeding the rng
    setup_seed();

    // super-loop
    while(1)
    {   
        screen.ShowAd(adChooser.chooseNextAd(&companies));
        screen.WriteChar(adChooser.chooseNextChar(&characters));
    }
    
    return 0;
}