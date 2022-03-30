#include "data.h"

void Data::vider() {
    //arbre_magasin.vider();
    //stock_inventaire.vider();
}

void Data::inserer_magasin(string& nom,PointST& point) 
{
    if (! inventaire.contient(nom) ) 
    {
        Magasin magasin(nom,point);
        inventaire[magasin];
        cout << "OK" << endl;
    }
    else{
        ERREUR_AJOUT_MAGASIN_DOUBLE(nom,point);
    }
}

Magasin Data::obtenir_magasin(string& nom) {
    assert(inventaire.contient(nom));
    Magasin m(nom);
    IterInventaire iter = inventaire.rechercher(m);
    return iter.cle();
}

void Data::inserer_produit( 
    string nom_produit,
    Date date_expiration,
    string nom_magasin, 
    int nombre_unite ) 
{
    assert(nombre_unite > 0);
    IterInventaire iter_magasins = inventaire.rechercher(nom_magasin);

    if ( ! iter_magasins )
    {
        std::cout << "Erreur : Le magasin " << nom_magasin << "n'est pas inscrit" << std::endl;
        ERREUR_MAGASIN_NULL(nom_magasin); return;
    }
    else 
    {
        IterProduits iter_produits = inventaire[iter_magasins.cle()].rechercher(nom_produit);
        if (! iter_produits) 
        {
            inventaire[iter_magasins.cle()][nom_produit];
            IterProduits iter_produits = inventaire[iter_magasins.cle()].rechercher(nom_produit);
            inventaire[iter_magasins.cle()][iter_produits.cle()][date_expiration];
            IterDate iter_date = inventaire[iter_magasins.cle()][iter_produits.cle()].rechercher(date_expiration);
            inventaire[iter_magasins.cle()][iter_produits.cle()][iter_date.cle()] = nombre_unite;
        } 
        else 
        {   
            IterDate iter_date = inventaire[iter_magasins.cle()][iter_produits.cle()].rechercher(date_expiration);
            if (! iter_date) {
                inventaire[iter_magasins.cle()][iter_produits.cle()][date_expiration];
                IterDate iter_date = inventaire[iter_magasins.cle()][iter_produits.cle()].rechercher(date_expiration);
                inventaire[iter_magasins.cle()][iter_produits.cle()][iter_date.cle()] = nombre_unite;
            }
            else {
                inventaire[iter_magasins.cle()][iter_produits.cle()][iter_date.cle()] += nombre_unite;
            }
        }
        cout << "OK" << endl;
        return;
    }
}

void Data::afficher_inventaire(string nom_magasin) 
{
    IterInventaire iter_magasins = inventaire.rechercher(nom_magasin);
    if (iter_magasins) 
    {
        IterProduits iter_produit = inventaire[iter_magasins.cle()].debut();
        for (;iter_produit;++iter_produit) 
        {
            int total = 0;
            IterDate iter_date = inventaire[iter_magasins.cle()][iter_produit.cle()].debut();
            for (;iter_date;++iter_date) 
            {
                total += inventaire[iter_magasins.cle()][iter_produit.cle()][iter_date.cle()];
            }

            string nom = iter_produit.cle();
            if ( total > 0 ) 
                cout << nom << " " << total << "\t";
        }
        cout << ";" << endl;
    }
}

void Data::nettoyer_inventaire(Date nouvelle_date) 
{
    IterInventaire iter_magasins = inventaire.debut();
    if (iter_magasins) 
    {
        IterProduits iter_produit = inventaire[iter_magasins.cle()].debut();
        for (;iter_produit;iter_produit) 
        {
            IterDate iter_date = inventaire[iter_magasins.cle()][iter_produit.cle()].debut();
            for (;iter_date;++iter_date) 
            {
                if ( iter_date.cle() < nouvelle_date )
                    inventaire[iter_magasins.cle()][iter_produit.cle()][iter_date.cle()] = 0;
            }
        }
    }
}

bool Data::ramasser_commande(Panier& panier, string& magasin) {

    IterInventaire iter_magasins = inventaire.rechercher(magasin);
    IterateurPanier iter_panier = panier.iterateur();
    assert(iter_magasins);
    bool complet = true;

    for (;iter_panier;++iter_panier) 
    {
        string nom_produit = iter_panier.cle();
        IterProduits iter_produits = inventaire[iter_magasins.cle()].debut();
        bool trouve = false;

        for(;iter_produits && !trouve;++iter_produits) 
        {
            if (iter_panier.cle() == iter_produits.cle() ) 
            {
                int quantite_dispo = 0;
                IterDate iter_date = inventaire[iter_magasins.cle()][iter_produits.cle()].debut();
                while (quantite_dispo < iter_panier.valeur() && iter_date) 
                {
                   quantite_dispo += inventaire[iter_magasins.cle()][iter_produits.cle()][iter_date.cle()];
                }
                if ( quantite_dispo >= iter_panier.valeur() ) 
                {
                    IterDate iter_d = inventaire[iter_magasins.cle()][iter_produits.cle()].debut();
                    while (iter_d && quantite_dispo > 0 ) 
                    {
                        if (iter_d.valeur() >= quantite_dispo) 
                        {
                            quantite_dispo = 0;
                            inventaire[iter_magasins.cle()][iter_produits.cle()][iter_date.cle()] = 0;
                        }
                        else
                        {
                            quantite_dispo -= iter_d.valeur();
                            inventaire[iter_magasins.cle()][iter_produits.cle()][iter_date.cle()] -= iter_d.valeur();
                        }
                    }
                }
                else {
                    if (complet) 
                        cout << "MANQUE ";
                    cout <<  iter_panier.cle() << " " << iter_panier.valeur() << " ";
                }
            }
        }
    }
}