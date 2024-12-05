#ifndef AD_CHOOSER_H
#define AD_CHOOSER_H

#include "companies.h"

class AdChooser
{
    private:
        char currentCompanyIndex;
        char currentAdIndex;

    public:
        AdChooser();
        Message* chooseNextAd(Companies *companies);
        char chooseNextCompany(Companies *companies);
        char chooseNextMessage(Company *company);

        void setCurrentAdIndex(char currentAdIndex);
        void setCurrentCompanyIndex(char currentCompanyIndex);

        char getCurrentCompanyIndex();
        char getCurrentAdIndex();

};

#endif