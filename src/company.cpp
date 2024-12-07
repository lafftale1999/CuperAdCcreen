#include "../include/company.h"
#include <string.h>

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