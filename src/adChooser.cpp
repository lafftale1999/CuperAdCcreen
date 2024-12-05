#include "../include/adChooser.h"
#include "stdlib.h"
#include "time.h"

AdChooser::AdChooser()
{
    this->currentAdIndex = -1;
    this->currentCompanyIndex = -1;
    srand(time(NULL));
}

Message AdChooser::chooseNextAd(Companies *companies)
{   
    this->currentCompanyIndex = chooseNextCompany(companies);
    this->currentAdIndex = chooseNextMessage(&companies->getCompany(currentCompanyIndex));

    return companies->getCompany(currentCompanyIndex).getMessages().getMessage(currentAdIndex);
}

int AdChooser::chooseNextCompany(Companies *companies)
{
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

int AdChooser::chooseNextMessage(Company *company)
{
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