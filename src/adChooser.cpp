#include "../include/adChooser.h"
#include <stdlib.h>
#include <avr/pgmspace.h>

AdChooser::AdChooser()
{
    this->currentCompanyIndex = -1;
}

Message AdChooser::chooseNextAd(CompaniesPROGMEM *companies)
{   
    this->currentCompanyIndex = chooseNextCompany(companies);

    CompanyPROGMEM companyFromPROGMEM;
    memcpy_P(&companyFromPROGMEM, &companies[this->currentCompanyIndex], sizeof(CompanyPROGMEM));

    Company currentCompany = Company(companyFromPROGMEM);

    return this->chooseNextMessage(&currentCompany);
}

int AdChooser::chooseNextCompany(CompaniesPROGMEM *companies)
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

char AdChooser::getCurrentCompanyIndex()
{
    return this->currentCompanyIndex;
}