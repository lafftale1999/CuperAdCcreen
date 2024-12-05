#include <stdio.h>
#include "include/adChooser.h"
#include "include/lcd.h"
#include "string.h"
#include "include/utils.h"

int main()
{   
    // creating and setting screen
    HD44780 screen;
    screen.Initialize();
    screen.Clear();

    // creating companies
    Companies companies;
    companies.addCompany(Company("Hederlige Harrys Bilar", 5000, "Buy your car from Harrys,scroll,A good deal (for Harry),plain,Hederlige Harrys Bilar,blink,")); // 334
    companies.addCompany(Company("Farmor Ankas Pajer AB", 3000, "Buy pie from Gramma Duck,scroll,Hurry before Marten eats it,plain,")); // 551
    companies.addCompany(Company("Svarte Petters Svartbyggen", 1500, "Let Petter build for you,scroll,No tax? Call Petter!,plain,")); // 
    companies.addCompany(Company("Goofy's Detective Agency", 4000, "Mysteries? Call Goofy,plain,Goofy kirr the biff,plain,"));
    companies.addCompany(Company("CuperAds", 1000, "Looking to be seen? Call us!,scroll,"));
    
    // totalt 14500kr
    companies.createAdSlots();

    // creating adchooser
    AdChooser adChooser;

    setup_seed();

    while(1)
    {   

        screen.ShowAd(adChooser.chooseNextAd(&companies));
        screen.Clear();
    }
    
    return 0;
}