#include "../include/adChooser.h"
#include <stdlib.h>
#include <stdio.h>
#include <avr/pgmspace.h>

AdChooser::AdChooser()
{
    this->currentCompanyIndex = -1;
}

Company AdChooser::chooseNextCompany(const CompaniesPROGMEM *companies)
{
    int rnd;

    while(1)
    {
        rnd = rand() % 1001;

        for(int i = 0; i < pgm_read_word(&companies->size); i++)
        {   
            if(rnd < pgm_read_word(&companies->companies[i].slotEnd))
            {
                if(this->currentCompanyIndex == i) break;

                this->currentCompanyIndex = i;

                CompanyPROGMEM company;
                memcpy_P(&company, &companies->companies[i], sizeof(CompanyPROGMEM));
                return Company(company);
            }
        }
    }
}

int AdChooser::chooseNextMessage(Company *company)
{
    int rnd = rand() % company->getMessages().getSize();

    return rnd;
}

void AdChooser::setCurrentCompanyIndex(char currentCompanyIndex)
{
    this->currentCompanyIndex = currentCompanyIndex;
}

int AdChooser::getCurrentCompanyIndex()
{
    return this->currentCompanyIndex;
}