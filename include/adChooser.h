#ifndef AD_CHOOSER_H
#define AD_CHOOSER_H

#include "company.h"
#include "characters.h"

class AdChooser
{
    private:
        int currentCompanyIndex;

    public:
        AdChooser();

        Character chooseNextChar(const CharactersFromPROGMEM *characters);
        Message chooseNextAd(const CompaniesPROGMEM *companies);
        int chooseNextCompany(const CompaniesPROGMEM *companies);
        Message chooseNextMessage(Company *company);

        void setCurrentCompanyIndex(char currentCompanyIndex);

        int getCurrentCompanyIndex();

};

#endif