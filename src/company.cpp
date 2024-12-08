#include "../include/company.h"
#include <string.h>
#include <avr/pgmspace.h>

CompaniesPROGMEM init_companies()
{
    CompaniesPROGMEM companies PROGMEM = 
    {
        {
            {"Hederlige Harrys Bilar", 5000, 344, "Buy your car from Harrys,scroll,A good deal (for Harry),plain,Hederlige Harrys Bilar,blink,"},
            {"Farmor Ankas Pajer AB", 3000, 551, "Buy pie from Gramma Duck,scroll,Hurry before Marten eats it,plain,"},
            {"Svarte Petters Svartbyggen", 1500, 655, "Let Petter build for you,scroll,No tax? Call Petter!,plain,"},
            {"Goofy's Detective Agency", 4000, 931, "Mysteries? Call Goofy,plain,Goofy kirr the biff,plain,"},
            {"CuperAds", 1000, 1000, "Looking to be seen? Call us!,scroll,"},
        },
        COMPANIES_IN_LIST,
        14500
    };

    return companies;
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