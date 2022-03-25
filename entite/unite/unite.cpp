#include "unite.h"

Unite::Unite(string& nom, Date& date)
{
    nom_produit = nom;
    date_expiration = date;
}

// Unite::~Unite()
// {
//     nom_produit.clear();
//     nom_produit = nullptr;
// }

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
        if (date_expiration < autre.date_expiration) 
            return true; 
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

string Unite::nom() {
    return nom_produit;
}

Date Unite::date() {
    return date_expiration;
}