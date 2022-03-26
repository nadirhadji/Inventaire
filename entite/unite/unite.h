#if !defined(_UNITE__H_)
#define _UNITE__H_

#include <string.h>
#include "../date/date.h"
using namespace std;

class Unite
{       
    private:
        string nom_produit;
        Date date_expiration;

    public:
        Unite(string&,Date&);
        // ~Unite();
        bool operator == (const Unite& u) const;
        bool operator < (const Unite& u) const;
        bool operator > (const Unite& u) const;
        void operator = (const Unite& u);
        string nom();
        Date date();
    };

#endif