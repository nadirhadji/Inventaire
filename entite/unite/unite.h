#if !defined(_UNITE__H_)
#define _UNITE__H_

#include <assert.h>
#include "../date/date.h"
using namespace std;

class Unite
{       
    private:
        string nom_produit;
        Date date_expiration;
        int quantite;

    public:
        Unite(string&,Date&,int&);
        Unite(string&);
        void ajouter_quantite(int&);
        void enveler_quantite(int&);
        void quantite_a_0();
        // ~Unite();
        bool operator == (const Unite& u) const;
        bool operator < (const Unite& u) const;
        bool operator > (const Unite& u) const;
        void operator = (const Unite& u);
        bool egale_nom(const string&) const;
    
    friend class Data;
    friend class Recommandation;
};

#endif