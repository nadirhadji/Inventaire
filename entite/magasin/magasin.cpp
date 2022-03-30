#include "magasin.h"

Magasin::Magasin() {
    nom = "null";
}

Magasin::Magasin(const Magasin& autre) {
    nom = autre.nom;
    position = autre.position;
}

Magasin::Magasin(string& str,PointST& p) {
    nom = str;
    position = p; 
}

Magasin::Magasin(const string& n)
{
    nom = n;
}

Magasin::~Magasin()
{
    nom.clear();
}

void Magasin::operator = ( const Magasin& autre) 
{
    nom = autre.nom;
    position = autre.position;
}

bool Magasin::operator == ( const Magasin& autre) const
{
    return nom == autre.nom;
}

bool Magasin::operator < ( const Magasin& autre) const
{
    return nom < autre.nom;
}   

bool Magasin::operator > ( const Magasin& autre) const 
{
    return nom > autre.nom;
}