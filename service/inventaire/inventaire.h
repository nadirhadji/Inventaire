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
using namespace std;

#define ERREUR_MAGASIN_NULL(nom) \
    cout << "Erreur : Le magasin " << nom << "n'est pas inscrit" << endl; \

#define ERREUR_AJOUT_MAGASIN_DOUBLE(nom,point) \
    cout << "Avertissement : L'epicerie" << nom << " deja presente au : " << point << "\n" \
    << "La commande PLACER est ignorée" << endl;

class Inventaire
{
    private:
        ArbreMap<string,PointST> map_magasin;
        ArbreMap< Unite , ArbreMap<string,int> > map_inventaire;
        Magasin obtenir_magasin(string nom_magasin);
    
    public:
        void vider();
        void inserer_magasin(string,PointST);
        void inserer_produit ( 
            string nom_produit,
            Date date_expiration,
            string nom_magasin, 
            int nb_unite
        );
        void afficher_inventaire(string nom_magasin);
        void nettoyer_inventaire(Date date);
};
#endif