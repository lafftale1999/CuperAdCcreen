#include "../include/company.h"
#include <string.h>
#include <avr/pgmspace.h>

const CompaniesPROGMEM companies PROGMEM = 
{
    {
        {"HEDERLIGE HARRYS BILAR AB", 
        5000, 
        344, 
        "BUY YOUR CAR FROM HARRYS,scroll,A GOOD DEAL (FOR HARRY),plain,GIVE ME YOUR MONAY,blink,",
        {
            0b01010, 0b11111, 0b10000, 0b11111,
            0b00001, 0b11111, 0b01010, 0b00000
        },
        REGULAR
        },

        {"GRAMMY DUCK'S PIES AB",
        3000,
        551,
        "BUY PIE FROM GRAMMY DUCK,scroll,MAKING PEOPLE FLOAT SINCE 1964,plain,",
        {
            0b00100, 0b10010, 0b01001, 0b10010,
            0b00000, 0b01110, 0b10001, 0b11111
        },
        REGULAR
        },

        {"PETTER'S HANDYMAN AB",
        1500,
        655,
        "LET BETTER DO THE BUILDING,scroll,NOW TAXFREE! CALL PETTER TODAY,plain,",
        {
            0b00000, 0b00001, 0b01111, 0b10101,
            0b00100, 0b00100, 0b00100, 0b00100
        },
        SPECIAL
        },

        {"GOOFY DETECTIVE AGENCY AB",
        4000,
        931,
        "MYSTERIES? CALL GOOFY!,plain,GOOFY KIRR THE BIFF,plain,",
        {
            0b01110, 0b10001, 0b10001, 0b10001,
            0b01110, 0b00100, 0b00010, 0b00001
        },
        REGULAR
        },

        {"CUPERADS",
        1000,
        1000,
        "LOOKING TO BE CEEN? CALL US!,scroll,",
        {
            0b11101, 0b10000, 0b11101, 0b00000,
            0b10111, 0b00101, 0b10111, 0b00101
        },
        REGULAR
        }
    },
    COMPANIES_IN_LIST,
    14500
};

const CompaniesPROGMEM* init_companies()
{
    return &companies;
}

Company::Company()
{
    setName("Unkown\n");
}

Company::Company(char name[MAX_STRING_LENGTH], int payment, char messages[])
{
    setName(name);
    setPayment(payment);
    createMessages(messages);
}

Company::Company(CompanyPROGMEM company)
{
    setName(company.name);
    setPayment(company.payment);
    createMessages(company.messages);
    this->logo = Character(company.bitMap);
    setDemand(company.demand);
}

void Company::setName(char name[MAX_STRING_LENGTH])
{
    this->name[0] = '\0';
    strcpy(this->name, name);
}

void Company::setPayment(int payment)
{
    this->payment = payment;
}

void Company::setDemand(Demand demand)
{
    this->demand = demand;
}

void Company::createMessages(char messages[])
{
    char message[MAX_STRING_LENGTH];
    char effect[7];

    int index = 0;
    int attributes = 0;

    for(int i = 0; i < strlen(messages); i++)
    {
        if (messages[i] != ',')
        {
            switch(attributes)
            {
                case 0:
                    message[index++] = messages[i];
                    continue;

                case 1:
                    effect[index++] = messages[i];
                    continue;
            }
        }

        switch(attributes)
        {
            case 0:
                message[index] = '\0';
                break;

            case 1:
                effect[index] = '\0';
                break;
        }

        attributes++;
        index = 0;

        if(attributes == 2)
        {
            this->messages.addMessage(Message(message, effect));
            attributes = 0;
        }
    }
}

char* Company::getName()
{
    return this->name;
}

int Company::getPayment()
{
    return this->payment;
}

Messages Company::getMessages()
{
    return this->messages;
}

Character Company::getLogo()
{
    return this->logo;
}

Demand Company::getDemand()
{
    return this->demand;
}