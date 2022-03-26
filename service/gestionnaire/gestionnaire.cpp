#include "gestionnaire.h"
#include "../../commande.h"

//Public 
Gestionnaire::Gestionnaire() {
    inventaire_globale = new Inventaire();
    cout << "Constructeur Gestionnaire" << endl;
}

Gestionnaire::~Gestionnaire() {
    delete inventaire_globale;
    inventaire_globale = nullptr;
}

//Private
void Gestionnaire::recommander(istream& entree) {
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

void Gestionnaire::ramasser(istream& entree) {
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
        Unite unite(nomproduit,dateexpiration);
        cout << "Pre appel approvisionner" << endl;
        inventaire_globale->inserer_produit(unite,nomepicerie,quantite);
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
    Magasin m = Magasin(nom,position);
    inventaire_globale->inserer_magasin(m);
}

void Gestionnaire::inventaire(istream& entree) {
    string nomepicerie;
    char pointvirgule=0;
    entree >> nomepicerie>> pointvirgule;
    assert(pointvirgule==';');
    // TODO
    cout << "?";
}

//DONE
void Gestionnaire::date(istream& entree) {
    char pointvirgule=0;
    Date temp_date;
    entree >> temp_date >> pointvirgule;
    assert(pointvirgule==';');
    if ( date_courante.modifier(temp_date) )
        cout << "OK" << endl;
}

//Private
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
    return 0;
}