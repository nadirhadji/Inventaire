#if !defined(_COMMANDE__H_)
#define _COMMANDE__H_

#include "../panier/panier.h"
#include "../point/pointst.h"

class Commande
{

  private:
    PointST point_initial;
    Panier panier;
    double distance_max;
    int nb_magasins_max;
    
  public:
    Commande(Panier&,double&,int&,PointST&);
    //void inserer(string&, int& );
    //void vider();
    //bool contient(string& s);
    //bool contient(Pile<string>& pile);
    //bool operator == (const Commande& autre) const;
  
  friend class Data;
  friend class Recommandation;
};

#endif