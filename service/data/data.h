/*  AUTEUR(S):
    1) Nadir Hadji - HADN08069703
*/
#if !defined(_INVENTAIRE__H_)
#define _INVENTAIRE__H_

#include <iostream>
#include <string>
#include "../../structure/arbreavl.h"
#include "../../structure/arbremap.h"
#include "../../entite/unite/unite.h"
#include "../../entite/magasin/magasin.h"
#include "../../entite/commande/commande.h"
using namespace std;

using MapInventaire = ArbreMap<Magasin, ArbreMap<string, ArbreMap<Date,int>>>;
using IterInventaire = ArbreMap<Magasin, ArbreMap<string, ArbreMap<Date,int>>>::Iterateur;

using MapProduits = ArbreMap<string, ArbreMap<Date,int> >;
using IterProduits = ArbreMap<string, ArbreMap<Date,int> >::Iterateur;

using MapDate = ArbreMap<Date,int>;
using IterDate = ArbreMap<Date,int>::Iterateur;

#define ERREUR_MAGASIN_NULL(nom) \
    cout << "Erreur : Le magasin " << nom << "n'est pas inscrit" << endl; \

#define ERREUR_AJOUT_MAGASIN_DOUBLE(nom,point) \
    cout << "Avertissement : L'epicerie" << nom << " deja presente au : " << point << "\n" \
    << "La commande PLACER est ignorée" << endl;

class Data
{
    private:
        ArbreMap<Magasin,ArbreMap<string,ArbreMap<Date,int>>> inventaire;

    public:
        void vider();
        void inserer_magasin(string&,PointST&);
        Magasin obtenir_magasin(string&);
        void inserer_produit (string, Date, string, int);
        void afficher_inventaire(string nom_magasin);
        void nettoyer_inventaire(Date date);
        bool ramasser_commande(Panier& panier, string &epicerie);

    friend class Recommandation;
    friend class Magasin;
};

#endif