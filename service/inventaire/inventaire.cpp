#include "inventaire.h"

void Inventaire::vider() {
    //arbre_magasin.vider();
    //map_inventaire.vider();
}

void Inventaire::inserer_magasin(string nom,PointST point) 
{
    if (! map_magasin.contient(nom) ) 
    {
        map_magasin[nom] = point;
        cout << "OK" << endl;
    }
    else{
        ERREUR_AJOUT_MAGASIN_DOUBLE(nom,point);
    }
}

void Inventaire::inserer_produit( 
    string nom_produit,
    Date date_expiration,
    string nom_magasin, 
    int nombre_unite ) 
{
    assert(nombre_unite > 0);

    if (! map_magasin.contient(nom_magasin) )
    {
        std::cout << "Erreur : Le magasin " << nom_magasin << "n'est pas inscrit" << std::endl;
        ERREUR_MAGASIN_NULL(nom_magasin); return;
    }
    else 
    {
        Unite unite ( nom_produit,date_expiration);

        if ( ! map_inventaire.contient(unite) ) 
        {
            (map_inventaire[unite])[nom_magasin] = nombre_unite;   
            cout << "OK" << endl;
            return;
        }
        else 
        {   
            int nouvelle_quantite = (map_inventaire[unite])[nom_magasin] + nombre_unite;
            (map_inventaire[unite])[nom_magasin] = nouvelle_quantite;
            cout << "OK" << endl;
        }
    }
}

void Inventaire::afficher_inventaire(string nom_magasin) {

    ArbreMap<string,int> map;
    ArbreMap<Unite,ArbreMap<string,int>>::Iterateur iter = map_inventaire.debut();

    for (; iter ; ++iter) {
        if ( iter.valeur().contient(nom_magasin) ) {
            string produit = iter.cle().nom_produit;
            int quantite = (iter.valeur())[nom_magasin];
            if ( map.contient(produit) )
                map[produit] += quantite;
            else    
                map[produit] = quantite;
        }
    }

    for (ArbreMap<string,int>::Iterateur it = map.debut();it;++it) {
        cout << it.cle() << " " << it.valeur() << "\t"; 
    }
    cout << ";" << endl;
}

void Inventaire::nettoyer_inventaire(Date nouvelle_date) {

    ArbreMap<Unite,ArbreMap<string,int>>::Iterateur iter = map_inventaire.debut();
    for (; iter ; ++iter) {
        if (iter.cle().date_expiration <= nouvelle_date) {
            ArbreMap<string,int>::Iterateur it = map_inventaire[iter.cle()].debut();
            for ( ;it;++it) {
                (map_inventaire[iter.cle()])[it.cle()] = 0;
            }
        }
    }
}