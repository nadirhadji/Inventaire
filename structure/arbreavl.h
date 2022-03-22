/* UQAM / Département d'informatique
   INF3105 - Structures de données et algorithmes
   Squelette pour classe générique ArbreAVL<T> pour le Lab6 et le TP2.

   AUTEUR(S):
    1) Nadir Hadji - HADN08069703
*/

#if !defined(_ARBREAVL___H_)
#define _ARBREAVL___H_
#include <cassert>
#include "pile.h"

template <class T>
class ArbreAVL {

  public:
    ArbreAVL();
    ArbreAVL(const ArbreAVL&);
    ~ArbreAVL();

    void inserer(const T&);
    bool contient(const T&) const;
    bool vide() const;
    void vider();
    void enlever(const T&); // non requis pour le TP2.
    int  hauteur() const;
    void print();

    // Annonce l'existance d'une classe Iterateur.
    class Iterateur;
    
    // Fonctions pour obtenir un itérateur (position dans l'arbre)
    Iterateur debut() const;
    Iterateur fin() const;
    Iterateur rechercher(const T&) const;
    Iterateur rechercherEgalOuSuivant(const T&) const;
    Iterateur rechercherEgalOuPrecedent(const T&) const;

    // Accès aux éléments de l'arbre via un intérateur.
    const T& operator[](const Iterateur&) const;
    T& operator[](const Iterateur&);
    
    // Copie d'un arbre AVL.
    ArbreAVL& operator = (const ArbreAVL&);

  private:
    struct Noeud{
        Noeud(const T&);
        T contenu ;
        int equilibre ;
        Noeud *gauche ;
        Noeud *droite ;
    };
    Noeud* racine;

    // Fonctions internes.
    bool inserer(Noeud*&, const T&);
    bool contient(Noeud*, const T&) const;
    void print(Noeud*,int);
    void rotationGaucheDroite(Noeud*&);
    void rotationDroiteGauche(Noeud*&);
    void vider(Noeud*&);
    void copier(const Noeud*, Noeud*&) const;
    const T& max(Noeud*) const;
    bool enlever(Noeud*&, const T& e);

  public:
    // Sera présenté à la semaine #7
    class Iterateur{
      public:
        Iterateur(const ArbreAVL& a);
        Iterateur(const Iterateur& a);
        Iterateur(const ArbreAVL& a, Noeud* c);

        operator bool() const;
        bool operator!() const;
        bool operator==(const Iterateur&) const;
        bool operator!=(const Iterateur&) const;
        
        const T& operator*() const;

        Iterateur& operator++();
        Iterateur operator++(int);
        Iterateur& operator = (const Iterateur&);

      private:
        const ArbreAVL& arbre_associe;
        Noeud* courant;
        Pile<Noeud*> chemin;
        
      friend class ArbreAVL;
    };
};

//-----------------------------------------------------------------------------

template <class T>
ArbreAVL<T>::Noeud::Noeud(const T& c):
gauche(NULL), droite(NULL), equilibre(0), contenu(c)
{
}

template <class T>
ArbreAVL<T>::ArbreAVL() : racine(NULL)
{
}

template <class T>
ArbreAVL<T>::ArbreAVL(const ArbreAVL<T>& autre) : racine(NULL)
{
    copier(autre.racine, racine);
}

template <class T>
ArbreAVL<T>::~ArbreAVL()
{
    vider(racine);
}

//TODO
template <class T>
bool ArbreAVL<T>::contient(const T& element) const
{
    Iterateur iter = rechercher(element);
    return iter == true;
}

template <class T>
bool ArbreAVL<T>::contient(Noeud* noeud, const T& element) const {

    if (noeud == NULL)
        return false;
    else if (noeud->contenu == element)
        return true;
    else if (noeud->contenu > element)
        contient(noeud->gauche,element);
    else if (noeud->contenu < element)
        contient(noeud->droite,element);

    // Iterateur it = debut();
    // while(it.courant->contenu <= element){
    //     it.courant->contenu == element ? return true : it++;
    // }
    // return false;

}

//DONE
template <class T>
void ArbreAVL<T>::inserer(const T& element)
{
    inserer(racine, element);
}

//DONE
template <class T>
bool ArbreAVL<T>::inserer(Noeud*& noeud, const T& element)
{
    if( noeud == nullptr)
    {
        noeud = new Noeud(element);
        return true;
    }
    if(element < noeud->contenu){
        if(inserer(noeud->gauche, element))
        {
            noeud->equilibre++;
            if(noeud->equilibre == 0) return false;
            if(noeud->equilibre == 1) return true;
            assert(noeud->equilibre==2);
            if(noeud->gauche->equilibre == -1)
                rotationDroiteGauche(noeud->gauche);
            rotationGaucheDroite(noeud);
        }
        return false;
    }
    else if(noeud->contenu < element){
        if ( inserer(noeud->droite, element) )
        {
            noeud->equilibre--;
            if ( noeud->equilibre == 0 ) return false;
            if ( noeud->equilibre == -1 ) return true;
            assert(noeud->equilibre == -2);
            if (noeud->droite->equilibre == 1)
                rotationGaucheDroite(noeud->droite);
            rotationDroiteGauche(noeud);
        }
        return false;
    }

    noeud->contenu = element; 
    return false;
}

//DONE
template <class T>
void ArbreAVL<T>::rotationGaucheDroite(Noeud*& racinesousarbre)
{
    Noeud *temp = racinesousarbre->gauche;
    int  equilibre_a = temp->equilibre;
    int  equilibre_b = racinesousarbre->equilibre;
    int  new_equilibre_b = - ( equilibre_a > 0 ? equilibre_a : 0) - 1 + equilibre_b;
    int  new_equilibre_a = equilibre_a + ( new_equilibre_b < 0 ? new_equilibre_b : 0 ) - 1;

    // std::cout << "Gauche Droite" << std::endl;
    // std::cout << "equilibre a : " << equilibre_a << std::endl;
    // std::cout << "equilibre b : " << equilibre_b << std::endl;
    // std::cout << "n equilibre a : " << new_equilibre_a << std::endl;
    // std::cout << "n equilibre b : " << new_equilibre_b << std::endl;

    temp->equilibre = new_equilibre_a;
    racinesousarbre->equilibre = new_equilibre_b;
    racinesousarbre->gauche = temp->droite;
    temp->droite = racinesousarbre;
    racinesousarbre = temp;
}

//DONE
template <class T>
void ArbreAVL<T>::rotationDroiteGauche(Noeud*& racinesousarbre)
{
    Noeud *temp = racinesousarbre->droite;
    int  equilibre_b = racinesousarbre->equilibre;
    int  equilibre_a = temp->equilibre;

    int  new_equilibre_b = (equilibre_a > 0 ? equilibre_a : 0 ) + 1 + equilibre_b - equilibre_a;
    int  new_equilibre_a = (new_equilibre_b > 0 ? new_equilibre_b : 0 ) + 1 + equilibre_a;

    // std::cout << "Droite Gauche " << std::endl;
    // std::cout << "equilibre a : " << equilibre_a << std::endl;
    // std::cout << "equilibre b : " << equilibre_b << std::endl;
    // std::cout << "n equilibre a : " << new_equilibre_a << std::endl;
    // std::cout << "n equilibre b : " << new_equilibre_b << std::endl;

    temp->equilibre = new_equilibre_a;
    racinesousarbre->equilibre = new_equilibre_b;
    racinesousarbre->droite = temp->gauche;
    temp->gauche = racinesousarbre;
    racinesousarbre = temp;
}

template <class T>
void ArbreAVL<T>::print() {
    print(racine,10);
}

template <class T>
void ArbreAVL<T>::print(Noeud *n, int space) {
    // Base case
    if (n == NULL)
        return;
 
    // Increase distance between levels
    space += 10;
 
    // Process right child first
    print(n->droite, space);
 
    // Print current node after space
    // count
    std::cout << std::endl;
    for (int i = 10; i < space; i++)
        std::cout<<" ";
    std::cout << n->contenu << "\n";
 
    // Process left child
    print(n->gauche, space);
}

//DONE
template <class T>
bool ArbreAVL<T>::vide() const
{
    return racine == nullptr;
}

//DONE
template <class T>
void ArbreAVL<T>::vider(){
  vider(racine);
}

//DONE
template <class T>
void ArbreAVL<T>::vider(Noeud*& noeud)
{
    if (noeud != nullptr) {
        vider(noeud->gauche);
        vider(noeud->droite);
        delete noeud;
    }
}

//DONE
template <class T>
void ArbreAVL<T>::copier(const Noeud* source, Noeud*& noeud) const
{
    if (source != nullptr && source != noeud) 
    {
        noeud->contenu = source->contenu;
        noeud->equilibre = source->equilibre;

        if (source->gauche != nullptr) 
        {
            delete noeud->gauche;
            noeud->gauche = new Noeud();
            copier(source->gauche,noeud->gauche);
        }

        if (source->droite != nullptr) 
        {
            delete noeud->droite;
            noeud->droite = new Noeud();
            copier(source->droite,noeud->droite);
        }
    }
}

//DONE
template <class T>
int  ArbreAVL<T>::hauteur() const {

    Noeud *temp = racine;
    int h = 0;
    do {
        if (temp == NULL)
            return h;
        else if (temp->equilibre == 0 || temp->equilibre == 1) 
            temp = temp->gauche;
        else if ( temp->equilibre == -1)
            temp = temp->droite;
        ++h;
    } while (temp != NULL);
    return h;
}

//DONE
template <class T>
const T& ArbreAVL<T>::max(Noeud* n) const
{
    Noeud *buffer = n;
    while (buffer->droite != nullptr) {
        buffer = buffer->droite;
    }
    return buffer->contenu;
}

// L'enlèvement est optionnel (non requise pour le TP2)
template <class T>
void ArbreAVL<T>::enlever(const T& element)
{
    enlever(racine, element);
}

//TODO
template <class T>
bool ArbreAVL<T>::enlever(Noeud*& noeud, const T& element)
{
    if(element < noeud->contenu)
    {
        if(enlever(noeud->gauche, element))
        {
            // ...
        }
    }
    else if(element > noeud->contenu)
    {
        if (enlever(noeud->droite, element))
        {
            
        }
    }
    else if(element == noeud->contenu)
    {
        if (noeud->gauche==NULL && noeud->droite==NULL)
        {
            delete noeud;
            noeud = NULL;
            return true;
        }
        else
        {
            // ...
            return true;
        }
    }
}
//----------- L'enlèvement est optionnel (non requise pour le TP2) ----------//

//DONE
template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::debut() const
{
    Iterateur iter(*this);
    iter.courant = racine;
    if(iter.courant != nullptr) {
        while(iter.courant->gauche != nullptr) {
            iter.chemin.empiler(iter.courant);
            iter.courant = iter.courant->gauche;
        }
    }
    return iter;
}

//DONE
template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::fin() const
{
    return Iterateur(*this);
}

//DONE
template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercher(const T& e) const
{
    Iterateur iter(*this);
    Noeud *n = racine;

    while(n) {
        if ( n->contenu > e ) {
            iter.chemin.empiler(n);
            n = n->gauche;
        }
        else if (n->contenu < e ) 
            n = n->droite;
        else {
            iter.courant = n;
            return iter;
        }
    }
    iter.chemin.vider();
    return iter;
}

//DONE
template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuSuivant(const T& e) const
{
    Noeud *n = racine , *suivant = nullptr;
    while(n) {
        if ( n->contenu < e )
            n = n->droite;
        else if ( n->contenu > e ) {
            suivant = n;
            n = n->gauche;
        }
        else
            return rechercher(e);
    }
    if ( suivant != nullptr)
        return rechercher(suivant->contenu);
    return Iterateur(*this);
}

//DONE
template <class T>  
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuPrecedent(const T& e) const
{
    Noeud *n = racine , *dernier = nullptr;

    while(n) {
        if ( n->contenu < e ) {
            dernier = n;
            n = n->droite;
        }
        else if ( n->contenu > e )
            n = n->gauche;
        else    
            return rechercher(e);
    }
    if (dernier != nullptr)
        return rechercher(dernier->contenu);
    return Iterateur(*this);
}

template <class T>
const T& ArbreAVL<T>::operator[](const Iterateur& iterateur) const
{
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->contenu;
}

template <class T>
T& ArbreAVL<T>::operator[](const Iterateur& iterateur)
{
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->contenu;
}

template <class T>
ArbreAVL<T>& ArbreAVL<T>::operator=(const ArbreAVL& autre) {
    if(this==&autre) return *this;
    vider();
    copier(autre.racine, racine);
    return *this;
}

//----------------------- ITERATEUR -----------------------
template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL& a)
 : arbre_associe(a), courant(NULL)
{
}

template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL<T>::Iterateur& a)
: arbre_associe(a.arbre_associe)
{
    courant = a.courant;
    chemin = a.chemin;
}

// Pré-incrément
template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator++()
{    
    assert(courant);
    Noeud* suivant = courant->droite;

    while(suivant) {
        chemin.empiler(suivant);
        suivant = suivant->gauche;
    }
    if (!chemin.vide())
        courant = chemin.depiler();
    else    
        courant = nullptr;
    return *this;
}

// Post-incrément
template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::Iterateur::operator++(int)
{
    Iterateur copie(*this);
    operator++();
    return copie;
}

template <class T>
ArbreAVL<T>::Iterateur::operator bool() const
{
    return courant!=NULL;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!() const{
    return courant==NULL;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator==(const Iterateur& o) const{
    assert(&arbre_associe == &o.arbre_associe);
    return courant == o.courant;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!=(const Iterateur& o) const{
    assert(&arbre_associe==&o.arbre_associe);
    return courant!=o.courant;
}

template <class T>
const T& ArbreAVL<T>::Iterateur::operator *() const
{
    assert(courant != NULL);
    return courant->contenu;
}

template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator = (const Iterateur& autre){
    assert( &arbre_associe == &autre.arbre_associe );
    courant = autre.courant;
    chemin = autre.chemin;
    return *this;
}
//---------------------------------------------------------

#endif
