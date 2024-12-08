#ifndef AD_CHOOSER_H
#define AD_CHOOSER_H

#include "company.h"

class AdChooser
{
    private:
        int currentCompanyIndex;

    public:
        AdChooser();

        Company chooseNextCompany(const CompaniesPROGMEM *companies);
        int chooseNextMessage(Company *company);

        void setCurrentCompanyIndex(char currentCompanyIndex);

        int getCurrentCompanyIndex();

};

#endif