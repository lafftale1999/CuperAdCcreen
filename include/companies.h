#ifndef COMPANIES_H
#define COMPANIES_H

#include "company.h"

typedef struct
{
    CompanyPROGMEM companies[COMPANIES_IN_LIST];
    int size;
    long totalPaid;
}CompaniesPROGMEM;

#endif