#include "magasin.h"
Magasin::Magasin() {
    cout << "Constructeur default magasin" << endl;
}

Magasin::Magasin(const Magasin& autre) {
    nom_magasin = autre.nom_magasin;
    position_magasin = autre.position_magasin;
}

Magasin::Magasin( const string& str,  const PointST& p) {
    nom_magasin = str;
    position_magasin = p; 
}

Magasin::Magasin(string& nom)
{
    nom_magasin = nom;
}

Magasin::~Magasin()
{
    nom_magasin.clear();
}

void Magasin::operator = (const Magasin* autre) {
    nom_magasin = autre->nom_magasin;
    position_magasin = autre->position_magasin;
}   

void Magasin::operator = (const Magasin& autre) {
    cout << "je suis ici" << endl;
    nom_magasin = autre.nom_magasin;
    position_magasin = autre.position_magasin;
}

bool Magasin::operator == (const Magasin& autre) const {
    return nom_magasin == autre.nom_magasin;
}

bool Magasin::operator < (const Magasin& autre) const {
    return nom_magasin < autre.nom_magasin;
}   

bool Magasin::operator > (const Magasin& autre) const {
    return nom_magasin > autre.nom_magasin;
}

const string& Magasin::nom() const {
    return nom_magasin;
}

const PointST& Magasin::position() const {
    return position_magasin;
}