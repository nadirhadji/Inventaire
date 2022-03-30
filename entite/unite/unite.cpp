#include "unite.h"

Unite::Unite(string& nom, Date& date, int& q)
{
    nom_produit = nom;
    date_expiration = date;
    quantite = q;
}

Unite::Unite(string& nom) {
    nom_produit = nom;
}

// Unite::~Unite()
// {
//     nom_produit.clear();
//     nom_produit = nullptr;
// }
void Unite::ajouter_quantite(int& q) {
    quantite += q;
}

void Unite::quantite_a_0() {
    quantite = 0;
}

void Unite::enveler_quantite(int& q) {
    assert(q <= quantite);
    quantite -= q;
}

bool Unite::operator == (const Unite& autre) const {
    return nom_produit == autre.nom_produit && 
        date_expiration == autre.date_expiration;
}

bool Unite::operator < (const Unite& autre) const {
    if ( (*this) == autre)
        return false;
    else if (nom_produit == autre.nom_produit && 
            ! (date_expiration == autre.date_expiration) ) 
    {
        Date defaul(0,0,0);
        if (autre.date_expiration == defaul || date_expiration == defaul)
            return false;
        else if (date_expiration < autre.date_expiration) 
            return true; 
        else
            return false;
    }
    else
        return nom_produit < autre.nom_produit;
}

bool Unite::operator > (const Unite& autre) const {
    if ( (*this) == autre)
        return false;
    else if (nom_produit == autre.nom_produit && 
            ! (date_expiration == autre.date_expiration) ) 
    {
        if (date_expiration < autre.date_expiration) 
            return false; 
        return true;
    }
    else
        return nom_produit < autre.nom_produit;
}

void Unite::operator = (const Unite& u) {
    nom_produit = u.nom_produit;
    date_expiration = u.date_expiration;
}

bool Unite::egale_nom(const string& autre_nom) const {
    return nom_produit == autre_nom;
}