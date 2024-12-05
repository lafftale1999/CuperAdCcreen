#ifndef AD_CHOOSER_H
#define AD_CHOOSER_H

#include "companies.h"

class AdChooser
{
    private:
        char currentCompanyIndex;
        char currentAdIndex;
        unsigned long seed;

    public:
        AdChooser();
        Message chooseNextAd(Companies *companies);
        int chooseNextCompany(Companies *companies);
        int chooseNextMessage(Company *company);

        void setCurrentAdIndex(char currentAdIndex);
        void setCurrentCompanyIndex(char currentCompanyIndex);

        char getCurrentCompanyIndex();
        char getCurrentAdIndex();

};

#endif