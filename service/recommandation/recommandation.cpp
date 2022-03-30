#include "recommandation.h"

Recommandation::Recommandation(Data* d) {
    data = d;
}

void Recommandation::recommander(Commande& commande) 
{
    assert(data != nullptr);
    
    if ( initialiser_possibilite(commande.panier) ) 
    {
        Panier liste_produit_trouve;            //Initialiser a vide
        Pile<Magasin> pile_visite;              //Init a vide
        Pile<Magasin> pile_solution;            //Init a vide
        string origine = "origine";
        PointST point_origine = commande.point_initial;
        int distance_restante = trouver ( 
            commande.panier,
            liste_produit_trouve,
            pile_visite,
            pile_solution,
            point_origine,
            commande.distance_max,
            commande.nb_magasins_max
        );

        if (distance_restante != -1) {
            int distance = commande.distance_max - ( distance_restante + 
            pile_solution.tete().position.distance(commande.point_initial) );
            cout << distance;
            while ( ! pile_solution.vide()) {
                cout << " " << pile_solution.depiler().nom << "";
            }
            cout << endl;
        }
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
    Panier liste_produit_trouve, 
    Pile<Magasin> pile_visitee,
    Pile<Magasin> &pile_solution,
    PointST origine,
    double distance_disponible,
    int nb_deplacement_restent
    )
{
    cout << "Debut Trouver" << endl;
    bool option_trouve = false;
    double cout_efficient_min = distance_disponible / 1;
    Magasin magasin_elu;
    Panier panier_trouve;
    double distance_a_parcourir;
    IterateurPossibilite iterateur(possibilite);

    for (;iterateur;++iterateur) 
    {
        PointST courante = iterateur.cle().position;
        distance_a_parcourir = courante.distance(origine);
        bool distance_suffisante = distance_a_parcourir <= distance_disponible;
        bool magasin_visitee = pile_visitee.contient(iterateur.cle());

        if ( (!magasin_visitee) && distance_suffisante ) 
        {          
            double cout_efficient = distance_a_parcourir / 
                (iterateur.valeur().nb_produits - liste_produit_trouve.nb_produits);

            if (cout_efficient < cout_efficient_min) 
            {
                cout_efficient_min = cout_efficient;
                magasin_elu = iterateur.cle();
                panier_trouve = iterateur.valeur();
                option_trouve = true;
            }
        }
    }

    if (option_trouve) {
            liste_produit_trouve.inserer_panier(panier_trouve);
            pile_solution.empiler(magasin_elu);
            pile_visitee.empiler(magasin_elu);
            distance_disponible -= distance_a_parcourir;
            --nb_deplacement_restent;

             //liste_produit_trouve.inserer_panier(possibilite[magasin_elu]);
    }

    bool fin = (panier == liste_produit_trouve);

    if (fin) 
    {
        return distance_a_parcourir;
    }
    else if ( ! pile_solution.vide() )
    {
        if (option_trouve) 
            distance_a_parcourir += trouver(panier,liste_produit_trouve,pile_visitee,pile_solution,magasin_elu.position,distance_disponible,nb_deplacement_restent);
        else
        {
            Magasin precedent = pile_solution.depiler();
            distance_disponible += distance_a_parcourir;
            ++nb_deplacement_restent;
            distance_a_parcourir += trouver(panier,liste_produit_trouve,pile_visitee,pile_solution,precedent.position,distance_disponible,nb_deplacement_restent);
        }
    }
    return distance_a_parcourir;
}