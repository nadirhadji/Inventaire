#if !defined(__RECOMMANDER_H__)
#define __RECOMMANDER_H__

#include <cmath>
#include "../../entite/point/pointst.h"
#include "../../entite/magasin/magasin.h"
#include "../../entite/unite/unite.h"
#include "../../entite/commande/commande.h"
#include "../../entite/panier/panier.h"
#include "../../structure/arbremap.h"
#include "../../structure/pile.h"
#include "../data/data.h"
using namespace std;

using MapPossibilite = ArbreMap<Magasin,Panier>;
using IterateurPossibilite = ArbreMap<Magasin,Panier>::Iterateur;

#define IMPOSSIBLE() \
    cout << "IMPOSSIBLE" << endl; \

class Recommandation
{
    private:
        MapPossibilite possibilite;
        Data *data;

        bool initialiser_possibilite(Panier&);
        bool trouver2(Commande& commande);
        int trouver(    Panier&,
                        Panier,
                        Pile<Magasin>,
                        PointST,
                        double,
                        int
                    );
        double calculer_coefficient(double,int,int);
        bool est_candidat(Pile<Magasin>&, const Magasin&, double , double);
        double distance_magasins(const Magasin& m1, Magasin& m2);

    public:
        Pile<Magasin> pile_solution;
        Recommandation(Data*);
        void recommander(Commande&);
        void chercher(Commande&);  
};

#endif
