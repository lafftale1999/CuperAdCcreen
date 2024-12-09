#ifndef __COMPANY_H
#define __COMPANY_H

#include "config.h"
#include "messages.h"
#include "character.h"

typedef enum
{
    SPECIAL,
    REGULAR
}Demand;

typedef struct
{
    char name [MAX_STRING_LENGTH];
    int payment;
    int slotEnd;
    char messages[MAX_STRING_LENGTH * MAX_MESSAGES];
    uint8_t bitMap[MAX_BIT_BITMAP];
    Demand demand;
}CompanyPROGMEM;

typedef struct
{
    CompanyPROGMEM companies[COMPANIES_IN_LIST];
    int size;
    long totalPaid;
}CompaniesPROGMEM;

const CompaniesPROGMEM* getCompaniesPtr();

class Company
{
    private:
        char name[MAX_STRING_LENGTH];
        int payment;
        Messages messages;
        Character logo;
        Demand demand;

    public:
        Company();
        Company(char name[MAX_STRING_LENGTH], int payment, char messages[]);
        Company(CompanyPROGMEM company);

        void setName(char name[MAX_STRING_LENGTH]);
        void setPayment(int payment);
        void createMessages(char messages[]);
        void setDemand(Demand demand);

        char* getName();
        int getPayment();
        Messages getMessages();
        Character getLogo();
        Demand getDemand();
};

#endif