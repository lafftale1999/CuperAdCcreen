#include "../include/adChooser.h"
#include <stdlib.h>
#include <stdio.h>
#include <avr/pgmspace.h>

AdChooser::AdChooser()
{
    this->currentCompanyIndex = -1;
}

Character AdChooser::chooseNextChar(const CharactersFromPROGMEM *characters)
{
    return Character(characters->characters[rand() % characters->charactersInList]);
}

Message AdChooser::chooseNextAd(const CompaniesPROGMEM *companies)
{   
    this->currentCompanyIndex = chooseNextCompany(companies); // WORKS

    Company currentCompany = Company(companies->companies[this->currentCompanyIndex]);

    return this->chooseNextMessage(&currentCompany);
}

int AdChooser::chooseNextCompany(const CompaniesPROGMEM *companies)
{
    int rnd;

    while(1)
    {
        rnd = rand() % 1001;

        for(int i = 0; i < companies->size; i++)
        {   
            if(rnd < companies->companies[i].slotEnd)
            {
                if(this->currentCompanyIndex == i) break;

                return i;
            }
        }
    }
}

Message AdChooser::chooseNextMessage(Company *company)
{
    int rnd = rand() % company->getMessages().getSize();

    return company->getMessages().getMessage(rnd);
}

void AdChooser::setCurrentCompanyIndex(char currentCompanyIndex)
{
    this->currentCompanyIndex = currentCompanyIndex;
}

int AdChooser::getCurrentCompanyIndex()
{
    return this->currentCompanyIndex;
}