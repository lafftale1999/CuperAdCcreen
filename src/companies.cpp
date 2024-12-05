#include "../include/companies.h"

Companies::Companies()
{
    this->sizeOfCompanies = 0;
    this->totalPaid = 0;
}

void Companies::addCompany(Company company)
{
    this->companies[this->sizeOfCompanies++] = company;
    this->totalPaid += company.getPayment();
}

int Companies::getSize()
{
    return this->sizeOfCompanies;
}

Company* Companies::getCompanies()
{
    return this->companies;
}

Company& Companies::getCompany(int index)
{
    return this->companies[index];
}

long Companies::getTotalPaid()
{
    return this->totalPaid;
}

void Companies::createAdSlots()
{   
    long currentFloor = 0L;

    for (int i = 0; i < this->getSize(); i++)
    {   
        long part = currentFloor + (long)this->getCompany(i).getPayment() * 1000L / (long)this->totalPaid;
        this->getCompany(i).setSlotEnd(part);
        currentFloor = this->getCompany(i).getSlotEnd() + 1L;
    }
    
}