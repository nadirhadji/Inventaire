/*  AUTEUR(S):
    1) Nadir HAdji - HADN08069703
*/

#if !defined(__GESTIONNAIRE_H__)
#define __GESTIONNAIRE_H__

#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include "../entite/date/date.h"
#include "../entite/point/pointst.h"
#include "../service/inventaire/inventaire.h"
#include "../commande.h"
using namespace std;

class Gestionnaire
{   
    public:
        Gestionnaire();
        ~Gestionnaire();
        int exectuer(istream& entree);

    private:
        Inventaire *inventaire_globale;
        Date date_courante;
   
        /**
         * @brief 
         * 
         * -----------------------------------------------------------------------------------------
         * 
         * External : 
        *      - Inventaire :  Map< string::produit ; Map<string::nom_magasin ; int::quantité>> 
        *      - Epiceries  :  Map<string::nom_epicerie ; Pointst::point>
        *      - Commande   :  Commande 
        *                              Produits      : Map <Produit> 
        *                              Cout_transport 
        *                                      Point : localisation_initial_client
        *                                      int   : nb_max_magasins
        *                                      int   : max_distance a parcourir
        * 
        *       Produit :
        *                   string     : nom_produit
        *                   int        : quantité
         * Internal :
         * 
         *      Pile < string::nom_magasins>  : vide
         *      AVL  < localisation_produit > : localisations 
         * 
         *      Localisation_produit :
         *                          - int    : nb_epicerie
         *                          - string : nom_produit
         *                          - AVL    : nom_epiceries
         * 
         * ---------------------------------------------------------------------------------------
         * Pseudo_algo :
         * 
         *      Pile<string> pile;
         *      AVL<Localisation_produit> localisations;
         *      int distance_parcourue = 0;
         * 
         * DEBUT
         * 
         *      // Insertion dans un arbre AVL localisations les objets Localisation_produit
         *      // (ensemble des epicerie qui ont en stock le produit). les objects doivent 
         *      // etre triée en fonction du nombre d'epicerie ayant en stock le produit 
         *      POUR CHAQUE produit dans Produits
         *              Localisation_produit localisation = obtenir_localisations(Produit,Inventaire);
         *              localisations.inserer(localisation);
         *      FIN POUR
         * 
         *      POUR CHAQUE localisation dans localisations (parcours inordre) 
         * 
         *              SI ( localisation.nb_magasins == 0 )
         * 
         *                      Return IMPOSSIBLE;
         * 
         *              SINON ( pile est vide )
         * 
         *                      int distance_min;
         *                      
         *                      POUR CHAQUE nom_epicerie DANS localisation.nom_magasins
         * 
         *                          Epicerie e = epicerie.rechercher(nom_epicerie)
         *                          Point point_client = commande.cout_transport.point
         *                          Point point_epicerie = e.point
         *                          int distance = point_client.distance(point_epicerie);
         * 
         *                          SI ( distance_min > distance)
         *                              distance_min = distance
         *                              pile.empiler(nom_epicerie)
         *                          FIN SI
         * 
         *                       FIN POUR
         * 
         *                       distance_parcourue += distance_min;
         * 
         *              FIN SINON
         * 
         *              SINON ( pile non vide )
         * 
         *                      SI (localisation.nb_magasins == 1) 
         * 
         *                          string nom_epicerie = localisation.nom_epiceries.premier()
         *              
         *                          SI ( pile.contient(nom_epicerie) )
         *                                  break; (arreter boucle courante)
         *                          FIN SI
         * 
         *                          SI  ( pile.nb_elements == commande.cout_transport.nb_max_magasins)
         *                                        Return IMPOSSIBLE;
         *                          FIN SI
         * 
         *                          SINON
         *                              pile.empiler(nom_epicerie);
         *                      FIN SI
         * 
         *                      SINON
         *                          
         *                          string epicerie_elue;
         *                          int distance_minimale;
         * 
         *                          POUR CHAQUE nom_epicerie DANS localisation.nom_magasins 
         * 
         *                              SI ( pile.contient(nom_epicerie) )
         *                                  break; (fin de la boucle)
         * 
         *                              SINON  
         *                                  string tete_pile = pile.tete;
         *                                  Epicerie e_pile = epiceries.rechercher(tete_pile);
         *                                  Epicerie e_courante = epicerie.rechercher(nom_epicerie);
         *                                  int distance = e_pile.point.distance(e_courante.point);
         *                                  SI (distance < distance_minimale)
         *                                      distance_minimale = distance;
         *                                      epicerie_elue = nom_epicerie;
         *                                  FIN SI
         * 
         *                              FIN SINON
         *    
         *                          FIN POUR CHAQUE
         * 
         *                          pile.empiler(epicerie_elue);
         *                          distance_parcourue += distance_minimale;
         * 
         *                      FIN SINON
         * 
         *               FIN SINON
         * 
         *      FIN POUR CHAQUE
         * 
         *      modifier_inventaire(inventaire,pile,commande.produits);
         * 
         *      affichage_recommender(distance_parcourue,pile);
         * 
         * FIN
         *      
         * @param entree 
         */
        void recommander(istream& entree);
        void ramasser(istream& entree);
        void approvisionner(istream& entree);
        void placer(istream& entree);
        void inventaire(istream& entree);
        void date(istream& entree);
};

#endif