/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/
#include <iostream>
#include "epicerie.h"

istream& operator >> (istream& is, Commande& c){
    string nomproduit;
    is >> nomproduit;
    while(is && nomproduit!=";"){
	int quantite;
        is >> quantite;
        // À compléter: faire quelque chose avec c ?
        is >> nomproduit;
    }
    return is;
}
