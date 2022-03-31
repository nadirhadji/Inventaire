#include "commande.h"

Commande::Commande(Panier& p, double& dm, int& mx, PointST& po) {
    panier = p;
    distance_max = dm;
    nb_magasins_max = mx;
    point_initial = po;
}
