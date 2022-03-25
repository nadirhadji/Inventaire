#include "commande.h"

std::istream& operator >> (istream& is, Commande& c){
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