#include "include/adChooser.h"
#include "include/lcd.h"
#include "include/utils.h"

#include <avr/pgmspace.h>

int main()
{   
    // creating and setting screen
    HD44780 screen;
    screen.Initialize();
    screen.Clear();

    const CompaniesPROGMEM companies PROGMEM = 
    {
        {
            {"Hederlige Harrys Bilar", 5000, 344, "Buy your car from Harrys,scroll,A good deal (for Harry),plain,Hederlige Harrys Bilar,blink,"},
            {"Farmor Ankas Pajer AB", 3000, 551, "Buy pie from Gramma Duck,scroll,Hurry before Marten eats it,plain,"},
            {"Svarte Petters Svartbyggen", 1500, 655, "Let Petter build for you,scroll,No tax? Call Petter!,plain,"},
            {"Goofy's Detective Agency", 4000, 931, "Mysteries? Call Goofy,plain,Goofy kirr the biff,plain,"},
            {"CuperAds", 1000, 1000, "Looking to be seen? Call us!,scroll,"},
        },
        COMPANIES_IN_LIST,
        14500
    };

    // creating adchooser
    AdChooser adChooser;

    setup_seed();

    while(1)
    {   
        screen.ShowAd(adChooser.chooseNextAd(&companies));
    }
    
    return 0;
}