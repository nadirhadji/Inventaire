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
#include "../../entite/quantite/quantite.h"
using namespace std;

#define ERREUR_MAGASIN_NULL(nom) \
    cout << "Erreur : Le magasin " << nom << "n'est pas inscrit" << endl; \

#define ERREUR_AJOUT_MAGASIN_DOUBLE(nom,position) \
    cout << "Avertissement : L'epicerie" << nom << " deja presente au : " << position << "\n" \
    << "La commande PLACER est ignorée" << endl;

class Inventaire
{
    private:
        ArbreAVL<Magasin> *arbre_magasin;
        ArbreMap< Unite , ArbreAVL<Quantite> > *map_inventaire;
        Magasin obtenir_magasin(string nom_magasin);
    
    public:
        Inventaire();
        ~Inventaire();
        void vider();
        void inserer_magasin(Magasin&);
        void inserer_produit(Unite unite,string nom_magasin, int nb_unite);
};

#endif