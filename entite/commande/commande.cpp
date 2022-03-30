#include "commande.h"

Commande::Commande(Panier& p, double& dm, int& mx, PointST& po) {
    panier = p;
    distance_max = dm;
    nb_magasins_max = mx;
    point_initial = po;
}

// void Commande::inserer(string& str, int& n) 
// {
//     if (! panier.liste.contient(str))
//         panier.inserer(str,n);
//     ++nb_produits;
// }

// void Commande::vider() {
//     if (! panier.liste.vide()) {
//         panier.liste.vider();
//         nb_produits=0;
//     }
// }

// bool Commande::contient(string& s) {
//     return panier.liste.contient(s);
// }

// bool Commande::contient(Pile<string>& pile) {
//     return panier.contient_pile(pile);
// }

// bool Commande::operator == (const Commande& autre) const {
//     return (panier == autre.panier);
// }
