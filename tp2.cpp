/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2017 | TP2
    http://ericbeaudry.uqam.ca/INF3105/tp2/   

    AUTEUR(S):
     1) Nadir Hadji - HADN08069703
*/
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <limits>
#include "entite/date/date.h"
#include "entite/point/pointst.h"
#include "service/gestionnaire/gestionnaire.h"
using namespace std;

// int tp2(istream& entree){

//     Date maintenant;

//     while(entree){
        
//         string typecommande;
//         entree >> typecommande;
//         if(!entree) break; // détection fin ==> sortie
        
//         if(typecommande=="RECOMMANDER"){
//             PointST p;
//             int nbMaxEpiceries=0;
//             double maxdistance=0;
//             Commande c;
//             char deuxpoints=0;
//             entree >> p >> nbMaxEpiceries >> maxdistance >> deuxpoints >> c;
//             assert(deuxpoints==':');
//             // À compléter
//             // 1 - Trouver les combinaisons possibles d'epicirie 
//             //     En fonction du nb max d'epicerie et de la distance maximale
//             // 2 - Trier les combinaisons par distance - a +
//             // 3 - Pour chaque combinaison verifier le stock dispobible.
//             cout << "IMPOSSIBLE";
//         }else if(typecommande=="RAMASSER"){
//             Commande c;
//             entree >> c;
//             string nomepicerie;
//             entree >> nomepicerie;
//             while(entree && nomepicerie!=";"){
//                 // À compléter
//                 entree >> nomepicerie;
//             }
//             // À compléter
//             cout << "COMPLET";
//         }else if(typecommande=="APPROV"){
//             string nomepicerie;
//             char deuxpoints=0;
//             entree >> nomepicerie >> deuxpoints;
//             assert(deuxpoints==':');
//             string nomproduit;
//             entree >> nomproduit;
//             while(entree && nomproduit!=";"){
//                 int quantite;
//                 Date dateexpiration;
//                 entree >> quantite >> dateexpiration;
//                 // À compléter
//                 entree >> nomproduit;
//             }
//             // À compléter
//             cout << "OK";
//         }else if(typecommande=="PLACER"){
//             PointST position;
//             string nom;
//             char pointvirgule=0;
//             entree >> nom >> position >> pointvirgule;
//             assert(pointvirgule==';');
//             // À compléter
//             cout << "OK";
//         }else if(typecommande=="INVENTAIRE"){
//             string nomepicerie;
//             char pointvirgule=0;
//             entree >> nomepicerie>> pointvirgule;
//             assert(pointvirgule==';');
//             // À compléter
//             cout << "?";
//         }else if(typecommande=="DATE"){
//             char pointvirgule=0;
//             entree >> maintenant >> pointvirgule;
//             assert(pointvirgule==';');
//             // À compléter
//             cout << "OK";
//         }else{
//             cout << "Commande '" << typecommande << "' invalide!" << endl;
//             return 2;
//         }
//         cout << endl;
//         entree >> ws; // force la lecture d'un espace blanc.
//     }
//     return 0;
// }

int tp(istream& entree) {
    Gestionnaire handler;
    return handler.exectuer(entree);
}

// syntaxe d'appel : ./tp2 [nomfichier.txt]
int main(int argc, const char** argv){
   
    if(argc>1){
         std::ifstream entree_fichier(argv[1]);
         if(entree_fichier.fail()){
             std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
             return 1;
         }
         return tp(entree_fichier);
    }else
         return tp(std::cin);        

    return 0;
}

