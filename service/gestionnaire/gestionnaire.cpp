#include "gestionnaire.h"

//Public
int Gestionnaire::exectuer(istream& entree) {
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
        else if(typecommande=="DATE") //DONE
            date(entree);
        else if(typecommande == "END")
            return 0;
        else {
            cout << "Commande '" << typecommande << "' invalide!" << endl;
            return 2;
        }
    }
    data.vider();
    return 0;
}

//Private
void Gestionnaire::recommander(istream& entree) {
    PointST point;
    int nbMaxEpiceries=0;
    double maxdistance=0;
    Panier panier;
    char deuxpoints=0;
    entree >> point >> nbMaxEpiceries >> maxdistance >> deuxpoints >> panier;
    assert(deuxpoints==':');
    Commande commande(panier,maxdistance,nbMaxEpiceries,point);
    Recommandation service(&data);
    service.chercher(commande);
}

void Gestionnaire::ramasser(istream& entree) {
    Panier panier;
    entree >> panier;
    string nomepicerie;
    entree >> nomepicerie;
    while(entree && nomepicerie!=";"){
        data.ramasser_commande(panier,nomepicerie);
        entree >> nomepicerie;
    }
}

//DONE
void Gestionnaire::approvisionner(istream& entree) {
    string nomepicerie;
    char deuxpoints=0;
    entree >> nomepicerie >> deuxpoints;
    assert(deuxpoints==':');
    string nomproduit;
    entree >> nomproduit;
    while(entree && nomproduit != ";") {
        int quantite;
        Date dateexpiration;
        entree >> quantite >> dateexpiration;
        data.inserer_produit (
            nomproduit,
            dateexpiration,
            nomepicerie,
            quantite
        );
        entree >> nomproduit;
    }
}

//DONE
void Gestionnaire::placer(istream& entree) {
    PointST position;
    string nom;
    char pointvirgule=0;
    entree >> nom >> position >> pointvirgule;
    assert(pointvirgule==';');
    data.inserer_magasin(nom,position);
}

//DONE
void Gestionnaire::inventaire(istream& entree) {
    string nomepicerie;
    char pointvirgule=0;
    entree >> nomepicerie >> pointvirgule;
    assert(pointvirgule==';');
    data.afficher_inventaire(nomepicerie);
}

//DONE
void Gestionnaire::date(istream& entree) {
    char pointvirgule=0;
    Date temp_date;
    entree >> temp_date >> pointvirgule;
    assert(pointvirgule==';');
    cout << "Ancienne date : " << date_courante << endl;
    if ( date_courante.modifier(temp_date) ) {
        cout << "Nouvelle date " << date_courante << endl;
        data.nettoyer_inventaire(temp_date);
        cout << "OK" << endl;
    }
}