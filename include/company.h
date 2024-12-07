#ifndef COMPANY_H
#define COMPANY_H

#include "config.h"
#include "messages.h"

typedef struct
{
    char name [MAX_STRING_LENGTH];
    int payment;
    int slotEnd;
    char messages[MAX_STRING_LENGTH * MAX_MESSAGES];
}CompanyPROGMEM;

class Company
{
    private:
        char name[MAX_STRING_LENGTH];
        int payment;
        Messages messages;

    public:
        Company();
        Company(char name[MAX_STRING_LENGTH], int payment, char messages[]);
        Company(CompanyPROGMEM company);

        void setName(char name[MAX_STRING_LENGTH]);
        void setPayment(int payment);
        void createMessages(char messages[]);

        char* getName();
        int getPayment();
        Messages getMessages();
};

#endif