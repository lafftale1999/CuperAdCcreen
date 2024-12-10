#include "include/adChooser.h"
#include "include/lcd.h"
#include "include/utils.h"
#include "include/millis.h"

#include <avr/pgmspace.h>
#include <avr/interrupt.h>

int main()
{   
    // initializing millis library and starting the clock
    millis_init();

    // allowing interrupts to be able to fetch time from millis_get()
    sei();

    // creating and setting screen
    HD44780 screen;
    screen.Initialize();
    screen.Clear();

    // creating pointer to companies in PROGMEM
    const CompaniesPROGMEM* companiesPtr = getCompaniesPtr();

    // creating adchooser
    AdChooser adChooser;

    // seeding rand() - used for generating currentCompany and their next message
    setup_seed();

    while(1)
    {   
        Company currentCompany = adChooser.chooseNextCompany(companiesPtr);
        screen.ShowAd(&currentCompany, adChooser.chooseNextMessage(&currentCompany));
    }
    
    return 0;
}