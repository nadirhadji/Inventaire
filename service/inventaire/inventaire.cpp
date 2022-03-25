#include "inventaire.h"

Inventaire::Inventaire()
{
    arbre_magasin = new ArbreAVL<Magasin>();
    map_inventaire = new ArbreMap<Unite,ArbreAVL<Quantite>>();
}

Inventaire::~Inventaire()
{
    map_inventaire->vider();
    delete map_inventaire;
    map_inventaire = nullptr;
    
    arbre_magasin->vider();
    delete arbre_magasin;
    arbre_magasin = nullptr;
}

void Inventaire::inserer_magasin(Magasin& magasin) 
{
    if (! arbre_magasin->contient(magasin) ) 
    {
        arbre_magasin->inserer(magasin);
        cout << "OK" << endl;
    }
    else{
        ERREUR_AJOUT_MAGASIN_DOUBLE(magasin.nom(),magasin.position())
    }
}

void Inventaire::inserer_produit(Unite unite,string nom_magasin,int nb_unite) 
{
    assert(nb_unite > 0);
    Magasin buff_magasin = Magasin(nom_magasin);

    if (! arbre_magasin->contient(buff_magasin) )
    {
        ERREUR_MAGASIN_NULL(nom_magasin); return;
    }
    else {
        if ( ! map_inventaire->contient(unite) ) {

            ArbreAVL<Magasin>::Iterateur iter = arbre_magasin->rechercher(buff_magasin);
            ArbreAVL<Quantite> arbre_quantite = ArbreAVL<Quantite>();
            cout << "Je suis ici 3 " << buff_magasin.nom() << buff_magasin.position() << endl;
            cout << "check " << (*arbre_magasin)[iter].nom() << (*arbre_magasin)[iter].position() << endl;
            const string s = (*arbre_magasin)[iter].nom();
            const PointST p = (*arbre_magasin)[iter].position();
            const Magasin m =  Magasin(s,p);
            Quantite q = Quantite(m,nb_unite);
            cout << "Pre insertion arbre quantite local" << endl;
            arbre_quantite.inserer(q);
            cout << "Je suis ici 4" << endl;
            cout << "Je suis ici 5" << endl;
            map_inventaire->inserer(unite,arbre_quantite);
            cout << "Je suis ici 6" << endl;
        }
        else 
        {
            ArbreAVL<Quantite>::Iterateur iter = 
                ArbreAVL<Quantite>::Iterateur(map_inventaire->rechercher(unite).valeur());
            map_inventaire->rechercher(unite).valeur()[iter].remplir(nb_unite);
        }
    }
}
