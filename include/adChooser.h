#ifndef AD_CHOOSER_H
#define AD_CHOOSER_H

#include "companies.h"

class AdChooser
{
    private:
        int currentCompanyIndex;

    public:
        AdChooser();
        Message chooseNextAd(CompaniesPROGMEM *companies);
        int chooseNextCompany(CompaniesPROGMEM *companies);
        Message chooseNextMessage(Company *company);

        void setCurrentCompanyIndex(char currentCompanyIndex);

        char getCurrentCompanyIndex();

};

#endif