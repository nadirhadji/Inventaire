#if !defined(_QUANTITE__H_)
#define _QUANTITE__H_

#include <fstream>
#include <string.h>
#include "../magasin/magasin.h"

class Quantite
{
    private:
        Magasin magasin;
        int nombre_unite;

    public:
        Quantite();
        Quantite(const Magasin&, const int&);
        ~Quantite();
        bool vide();
        void vider();
        void remplir(int);
        bool consommer(int);
        bool operator < (const Quantite& u) const;
        bool operator > (const Quantite& u) const;
        bool operator == (const Quantite& u) const;
        Magasin epicerie() const;
        int valeur() const;
};

#endif