#include <stdio.h>
#include "include/adChooser.h"
#include "include/lcd.h"

int main()
{   
    // creating and setting screen
    HD44780 screen;
    screen.Initialize();
    screen.Clear();

    // creating companies
    Companies companies;
    companies.addCompany(Company("Hederlige Harrys Bilar", 5000, "Buy your car from Harrys,scroll,A good deal (for Harry),plain,Hederlige Harrys Bilar,blink,"));
    companies.addCompany(Company("Farmor Ankas Pajer AB", 3000, "Buy pie from Gramma Duck,scroll,Hurry before Marten eats it,plain,"));
    companies.addCompany(Company("Svarte Petters Svartbyggen", 1500, "Let Petter build for you,scroll,No tax? Call Petter!,plain,"));
    companies.addCompany(Company("Goofy's Detective Agency", 4000, "Mysteries? Call Goofy,plain,Goofy kirr the biff,plain,"));
    companies.addCompany(Company("CuperAds", 1000, "Looking to be seen? Call us!,scroll,"));
    
    // creating adchooser
    AdChooser adChooser;

    while(1)
    {
        screen.ShowAd(adChooser.chooseNextAd(&companies));
    }
    
    return 0;
}