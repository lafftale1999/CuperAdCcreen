#include "../include/adChooser.h"
#include "time.h"
#include "stdlib.h"

AdChooser::AdChooser()
{
    this->currentAdIndex = -1;
    this->currentCompanyIndex = -1;
}

Message* AdChooser::chooseNextAd(Companies *companies)
{
    this->currentCompanyIndex = chooseNextCompany(companies);
    this->currentAdIndex = chooseNextMessage(&companies->getCompany(currentCompanyIndex));

    return &companies->getCompany(currentCompanyIndex).getMessages().getMessage(currentAdIndex);
}

char AdChooser::chooseNextCompany(Companies *companies)
{
    srand(time(NULL));
    int rnd;

    while(1)
    {
        rnd = rand() % 1001;

        for(int i = 0; i < companies->getSize(); i++)
        {   
            if(rnd < companies->getCompanies()[i].getSlotEnd())
            {
                if(this->currentCompanyIndex == i) break;

                return i;
            }
        }
    }
}

char AdChooser::chooseNextMessage(Company *company)
{
    srand(time(NULL));
    int rnd = rand() % company->getMessages().getSize();

    return rnd;
}

void AdChooser::setCurrentAdIndex(char currentAdIndex)
{
    this->currentAdIndex = currentAdIndex;
}
void AdChooser::setCurrentCompanyIndex(char currentCompanyIndex)
{
    this->currentCompanyIndex = currentCompanyIndex;
}

char AdChooser::getCurrentCompanyIndex()
{
    return this->currentCompanyIndex;
}

char AdChooser::getCurrentAdIndex()
{
    return this->currentAdIndex;
}