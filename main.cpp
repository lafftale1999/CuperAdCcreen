#include "include/adChooser.h"
#include "include/lcd.h"
#include "include/utils.h"
#include "include/millis.h"

#include <avr/pgmspace.h>
#include <avr/interrupt.h>

int main()
{   
    // initializing millis library
    millis_init();

    sei();

    // creating and setting screen
    HD44780 screen;
    screen.Initialize();
    screen.Clear();

    // loading companies into PROGMEM
    const CompaniesPROGMEM companies PROGMEM = init_companies();

    // creating adchooser
    AdChooser adChooser;

    // seeding the rng
    setup_seed();

    // super-loop
    while(1)
    {   
        Company currentCompany = adChooser.chooseNextCompany(&companies);
        screen.ShowAd(&currentCompany, adChooser.chooseNextMessage(&currentCompany));
    }
    
    return 0;
}
