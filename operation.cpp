#include "operation.h"

//Private
void Operation::recommander(istream& entree) {
    PointST p;
    int nbMaxEpiceries=0;
    double maxdistance=0;
    Commande c;
    char deuxpoints=0;
    entree >> p >> nbMaxEpiceries >> maxdistance >> deuxpoints >> c;
    assert(deuxpoints==':');
    // À compléter
    // 1 - Trouver les combinaisons possibles d'epicirie 
    //     En fonction du nb max d'epicerie et de la distance maximale
    // 2 - Trier les combinaisons par distance - a +
    // 3 - Pour chaque combinaison verifier le stock dispobible.
    cout << "IMPOSSIBLE";
}

void Operation::ramasser(istream& entree) {
    Commande c;
    entree >> c;
    string nomepicerie;
    entree >> nomepicerie;
    while(entree && nomepicerie!=";"){
        // À compléter
        entree >> nomepicerie;
    }
    // À compléter
    cout << "COMPLET";
}

void Operation::approvisionner(istream& entree) {
    string nomepicerie;
    char deuxpoints=0;
    entree >> nomepicerie >> deuxpoints;
    assert(deuxpoints==':');
    string nomproduit;
    entree >> nomproduit;
    while(entree && nomproduit!=";"){
        int quantite;
        Date dateexpiration;
        entree >> quantite >> dateexpiration;
        // À compléter
        entree >> nomproduit;
    }
    // À compléter
    cout << "OK";
}

void Operation::placer(istream& entree) {
    PointST position;
    string nom;
    char pointvirgule=0;
    entree >> nom >> position >> pointvirgule;
    assert(pointvirgule==';');
    // TODO
    cout << "OK";
}

void Operation::inventaire(istream& entree) {
    string nomepicerie;
    char pointvirgule=0;
    entree >> nomepicerie>> pointvirgule;
    assert(pointvirgule==';');
    // TODO
    cout << "?";
}

void Operation::date(istream& entree) {
    char pointvirgule=0;
    Date temp_date;
    entree >> temp_date >> pointvirgule;
    assert(pointvirgule==';');
    //Valider Date 
    date_courante = temp_date;
    cout << "OK";
}

//Private

int Operation::exectuer(istream& entree) {
    while(entree){

        string typecommande;
        entree >> typecommande;
        if(!entree) break; // détection fin ==> sortie

        if (typecommande=="RECOMMANDER")
            recommander(entree);
        else if (typecommande=="RAMASSER")
            ramasser(entree);
        else if(typecommande=="APPROV")
            approvisionner(entree);
        else if(typecommande=="PLACER")
            placer(entree);
        else if(typecommande=="INVENTAIRE")
            inventaire(entree);
        else if(typecommande=="DATE")
            date(entree);
        else {
            cout << "Commande '" << typecommande << "' invalide!" << endl;
            return 2;
        }
    }
}