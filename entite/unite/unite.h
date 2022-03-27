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
        Unite(string&);
        // ~Unite();
        bool operator == (const Unite& u) const;
        bool operator < (const Unite& u) const;
        bool operator > (const Unite& u) const;
        void operator = (const Unite& u);
        bool egale_nom(const string&) const;
    
    friend class Inventaire;
};

#endif