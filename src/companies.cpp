#include "../include/companies.h"

int Companies::totalPaid = 0;

Companies::Companies()
{
    this->sizeOfCompanies = 0;
}

void Companies::addCompany(Company company)
{
    this->companies[this->sizeOfCompanies++] = company;
    totalPaid += company.getPayment();
}

int Companies::getSize()
{
    return this->sizeOfCompanies;
}

Company* Companies::getCompanies()
{
    return this->companies;
}

Company Companies::getCompany(int index)
{
    return this->companies[index];
}

void Companies::createAdSlots()
{   
    int currentFloor = 0;

    for(Company &company : this->companies)
    {
        company.setSlotEnd(currentFloor + (company.getPayment() * 1000) / totalPaid);
        currentFloor += company.getSlotEnd() + 1;
    }
}