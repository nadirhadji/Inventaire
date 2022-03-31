#include "panier.h"

//Private
std::istream& operator >> (istream& is, Panier& panier) {
    string nomproduit;
    is >> nomproduit;
    while(is && nomproduit!=";"){
	int quantite;
        is >> quantite;
        panier.inserer(nomproduit,quantite);
        is >> nomproduit;
    }
    return is;
}

//Public

Panier::~Panier() {
    nb_produits = 0;
}

Panier::Panier(const Panier& autre) 
{
    liste = autre.liste;
    nb_produits = autre.nb_produits;
}

bool Panier::vide() {
    if (nb_produits == 0)
        return true;
    return false;
}

int Panier::total() {
    return nb_produits;
}

void Panier::inserer(string& nouveau,int& quantite_nouveau) 
{
    if (! liste.contient(nouveau)) 
    {
        liste[nouveau] = quantite_nouveau;
        ++nb_produits;
    }
} 
      
void Panier::inserer_panier(Panier& autre_liste) 
{
    ArbreMap<string,int>::Iterateur iter_autre(autre_liste.liste);
    for(;iter_autre;++iter_autre) 
    {
        string new_nom = iter_autre.cle();
        if (! liste.contient(new_nom) ) 
        {
            int new_quantite = iter_autre.valeur();
            liste[new_nom] = new_quantite;
            ++nb_produits;
        }
    }
}

bool Panier::contient(string& nom_produit) 
{
    if (liste.contient(nom_produit))
        return true;
    return false;
}

bool Panier::contient_pile(Pile<string>& pile) {
    while(!pile.vide()) {
        string str = pile.depiler();
        if (! liste.contient(str))
            return false;
    }
    return true;
}

bool Panier::operator == (const Panier& autre_panier) const
{
    if (nb_produits != autre_panier.nb_produits )
        return false;
    
    ArbreMap<string,int>::Iterateur iter_courant(liste);
    ArbreMap<string,int>::Iterateur iter_autre(autre_panier.liste);
    for(;iter_courant || iter_autre; ++iter_autre , ++iter_courant) 
    {
        if ( iter_courant.cle() != iter_autre.cle())
            return false;
    }
    return true;
}

IterateurPanier Panier::iterateur() {
    return ArbreMap<string,int>::Iterateur(liste);
}