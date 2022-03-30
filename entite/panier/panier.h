#if !defined(_PANIER__H_)
#define _PANIER__H_

#include <string>
#include <iostream>
#include "../../structure/arbremap.h"

using namespace std;
using MapPanier = ArbreMap<string,int>;
using IterateurPanier = ArbreMap<string,int>::Iterateur;

class Panier {

  private : 
      MapPanier liste;
      int nb_produits;

  public :
    Panier();
    ~Panier();
    Panier(const Panier&);
    bool vide();
    int total();
    void inserer(string& nouveau,int& quantite_nouveau);
    void inserer_panier(Panier& autre_panier);
    bool contient_pile(Pile<string>& pile);
    bool contient(string& nom_produit);
    bool operator == (const Panier& autre_panier) const;
    IterateurPanier iterateur();

  friend istream& operator >> (istream& is, Panier& panier);
  friend class Recommandation;
  friend class Commande;
  friend class Data; 
};

#endif
