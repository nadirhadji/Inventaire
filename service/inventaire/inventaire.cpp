#include "inventaire.h"

void Inventaire::inserer_magasin(Magasin& magasin) 
{
    if (! arbre_magasin.contient(magasin) ) 
    {
        arbre_magasin.inserer(magasin);
    }
    else{
        ERREUR_AJOUT_MAGASIN_DOUBLE(magasin.nom(),magasin.position())
    }
}

void Inventaire::inserer_produit(Unite unite,string nom_magasin,int nb_unite) 
{
    assert(nb_unite > 0);
    const Magasin buff_magasin = Magasin(nom_magasin);

    if (! arbre_magasin.contient(buff_magasin) )
    {
        ERREUR_MAGASIN_NULL(nom_magasin); return;
    }
    else {

        ArbreAVL<Magasin>::Iterateur iter = arbre_magasin.rechercher(buff_magasin);
        const string s = arbre_magasin[iter].nom();
        const PointST p = arbre_magasin[iter].position();
        Magasin epicerie =  Magasin(s,p);

        if ( ! map_inventaire.contient(unite) ) {

            //ArbreAVL<Magasin> arbre_magasin;
            //ArbreMap< Unite , ArbreMap<Magasin,int> > map_inventaire;
            
            //ArbreMap<Magasin,int> map_quantite;
            //map_quantite[epicerie] = nb_unite;  
 
            (map_inventaire[unite])[epicerie] = nb_unite;
            cout << "Map Unite" << endl;
            return;
        }
        else 
        {   
            ArbreMap<Magasin, int> valeur_unite = map_inventaire.rechercher(unite).valeur();
            ArbreMap<Magasin, int>::Iterateur iter = valeur_unite.rechercher(buff_magasin);
            int nouvelle_quantite = iter.valeur() + nb_unite;
            (map_inventaire[unite])[iter.cle()] = nouvelle_quantite;
        }
    }
}