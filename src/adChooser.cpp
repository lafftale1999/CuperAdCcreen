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
    /**Every company have a "slotEnd" that symbolise their adslot wich is based on their payment / total payment * 1000.
     * As we are using PROGMEM - these have been hardcoded in to the PROGMEM in company.cpp
     * This algorithm randomly generates a number between 0-1000. The program then checks if rnd is smaller 
     * than the slotEnd, if not - check next company. After that it checks if the company is the currentcompany 
     * that is showing to avoid showing the same company twice in a row.
     */

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

                // copies the value at companies->companies[i] and creates a company
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