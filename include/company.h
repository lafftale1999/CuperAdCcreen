#ifndef COMPANY_H
#define COMPANY_H

#include "config.h"
#include "messages.h"

class Company
{
    private:
        char name[MAX_STRING_LENGTH];
        int payment;
        Messages messages;
        int slotEnd;

    public:
        Company();
        Company(char name[MAX_STRING_LENGTH], int payment, char messages[]);

        void setName(char name[MAX_STRING_LENGTH]);
        void setPayment(int payment);
        void createMessages(char messages[]);
        void setSlotEnd(int slotEnd);

        char* getName();
        int getPayment();
        Messages getMessages();
        int getSlotEnd();
};

#endif