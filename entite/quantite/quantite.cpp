#include <assert.h>
#include "quantite.h"

Quantite::Quantite() {
    cout << "Quantite constructeur vide" << endl;
    magasin = NULL;
}

Quantite::Quantite(const Magasin& autre_magasin, const int& autre_nombre)
{
    cout << "Quantite constructeur attriuts" << endl;
    magasin = autre_magasin;
    nombre_unite = autre_nombre;
}

Quantite::~Quantite() {
    vider();
}

bool Quantite::vide() {
    return nombre_unite == 0;
}

void Quantite::vider() {
    nombre_unite = 0;
}

void Quantite::remplir(int nb_unite) {
    assert ( !magasin.nom().empty() );
    nombre_unite += nb_unite;
}

bool Quantite::consommer(int nb_unite) {
    assert ( !magasin.nom().empty() );
    if ( nombre_unite > nb_unite ) {
       nombre_unite -= nb_unite;
        return true;
    }
    return false;
}

bool Quantite::operator < (const Quantite& q) const {
    return nombre_unite < q.valeur();
}

bool Quantite::operator > (const Quantite& q) const {
    return nombre_unite > q.valeur();
}

bool Quantite::operator == (const Quantite& q) const {
    return nombre_unite == q.valeur();
}

Magasin Quantite::epicerie() const {
    return magasin;
}

int Quantite::valeur() const {
    return nombre_unite;
}