#include "recommandation.h"

Recommandation::Recommandation(Data* d) {
    data = d;
}

void Recommandation::chercher(Commande& commande) {

    if ( initialiser_possibilite(commande.panier) ) 
        recommander(commande);
}

void Recommandation::recommander(Commande& commande) 
{
    assert(data != nullptr);
    
    Panier liste_trouve;                  //Initialiser a vide
    Pile<Magasin> pile_visite;           //Init a vide
    string origine = "";
    PointST point_origine = commande.point_initial;
    Magasin m(origine,point_origine);
    pile_solution.empiler(m);
    
    int distance_disponible = trouver ( 
        commande.panier,
        liste_trouve,
        pile_visite,
        point_origine,
        commande.distance_max,
        commande.nb_magasins_max
    );

    if (distance_disponible != 0) {
        PointST dernier = pile_solution.tete().position;
        PointST premier = commande.point_initial;
        double distance_retour = dernier.distance(premier);
        int distance = distance_disponible - distance_retour;
        int distance_parcourue = commande.distance_max - distance;
        cout << distance_parcourue << "m ";
        while ( ! pile_solution.vide() ) {
            cout << " " << pile_solution.depiler().nom << "";
        }
        cout << endl;
    }
}

bool Recommandation::initialiser_possibilite(Panier &panier) 
{
    assert(!panier.vide());
    ArbreMap<string,int>::Iterateur iter_panier = panier.iterateur();
    bool produit_manquant = false;

    for (;iter_panier && (!produit_manquant); ++iter_panier) 
    {
        bool produit_trouve = false;
        IterInventaire iter_magasins = data->inventaire.debut();
        for (;iter_magasins;++iter_magasins) 
        {
            IterProduits iter_produits = data->inventaire[iter_magasins.cle()].rechercher(iter_panier.cle());
            if ( iter_produits ) 
            {
                int quantite_dispo = 0;
                IterDate iter_date = data->inventaire[iter_magasins.cle()][iter_produits.cle()].debut();
                for(;quantite_dispo < iter_panier.valeur() && iter_date ; ++iter_date) 
                {
                    quantite_dispo += data->inventaire[iter_magasins.cle()][iter_produits.cle()][iter_date.cle()];
                }
                if ( quantite_dispo >= iter_panier.valeur() ) 
                {
                    string nom = iter_panier.cle();
                    int q = iter_panier.valeur();
                    possibilite[iter_magasins.cle()].inserer(nom,q);
                    produit_trouve = true;
                }
            }
        }
        if (! produit_trouve ) {
            IMPOSSIBLE(); return false;
        }
    }
    return true;
}

int Recommandation::trouver(
    Panier &panier, 
    Panier liste_trouve, 
    Pile<Magasin> pile_visitee,
    PointST origine,
    double distance_dispo,
    int nb_deplacement_restent
    )
{
    bool option_trouve = false;
    double cout_efficient_min = distance_dispo;
    Magasin magasin_elu;
    Panier panier_trouve;
    double distance_elue;
    IterateurPossibilite iter(possibilite);

    for (;iter;++iter) 
    {
        double distance = distance_magasins(iter.cle(),pile_solution.tete());

        if ( est_candidat(pile_visitee,iter.cle(),distance,distance_dispo) ) 
        {          
            double cout = calculer_coefficient(distance,
                iter.valeur().nb_produits, liste_trouve.nb_produits);

            if (cout < cout_efficient_min) 
            {
                cout_efficient_min = cout;
                magasin_elu = iter.cle();
                panier_trouve = iter.valeur();
                distance_elue = distance;
                option_trouve = true;
            }
        }
    }

    if (option_trouve) {
            liste_trouve.inserer_panier(panier_trouve);
            pile_solution.empiler(magasin_elu);
            pile_visitee.empiler(magasin_elu);
            distance_dispo -= distance_elue;
            --nb_deplacement_restent;
    }

    if ( (panier == liste_trouve) ) 
    {
        return distance_dispo;
    }
    else if ( ! pile_solution.vide() )
    {
        if (option_trouve) 
            distance_dispo -= trouver(
                panier,
                liste_trouve,
                pile_visitee,
                magasin_elu.position,
                distance_dispo,
                nb_deplacement_restent
            );
        else
        {
            Magasin precedent = pile_solution.depiler();
            distance_dispo += pile_solution.tete().position.distance(precedent.position);
            ++nb_deplacement_restent;
            distance_dispo += trouver ( 
                panier,
                liste_trouve,
                pile_visitee,
                precedent.position,
                distance_dispo,
                nb_deplacement_restent
            );
        }
    }
    else if ( pile_solution.vide() )
        return 0;
    else
        return distance_dispo;
}

double Recommandation::calculer_coefficient(double dist, int nb_prod_total, int nb_prod_ceuilli ) {
    double cout_efficient = dist / (dist - nb_prod_ceuilli);
}

double Recommandation::distance_magasins(const Magasin& m1, Magasin& m2) {
    PointST courante = m1.position;
    PointST org = m2.position;
    double distance = org.distance(courante);
    return distance;
}

bool Recommandation::est_candidat(Pile<Magasin>& pile_visite, const Magasin& m1, double dist, double dist_dispo) {

    bool distance_suffisante = dist <= dist_dispo;
    bool magasin_visitee = pile_visite.contient(m1) || pile_solution.contient(m1);
    return ( (!magasin_visitee) && distance_suffisante) ;
}