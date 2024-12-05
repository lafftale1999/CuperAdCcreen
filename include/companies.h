#ifndef COMPANIES_H
#define COMPANIES_H

#include "company.h"

class Companies
{
    private:
        Company companies[COMPANIES_IN_LIST];
        int sizeOfCompanies;
        long totalPaid;

    public:
        Companies();
        void addCompany(Company company);
        int getSize();
        Company* getCompanies();
        long getTotalPaid();
        void createAdSlots();

        Company& getCompany(int index);
};

#endif