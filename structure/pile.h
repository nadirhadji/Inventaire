/*  INF3105 | Structures de données et algorithmes
 *  UQAM | Département d'informatique | Automne 2017
 *  Pile pour les intérateur d'Arbre AVL pour le Lab6 et TP2
 *  http://ericbeaudry.ca/INF3105/
 */
#if !defined(__PILE__H__)
#define __PILE__H__

#include <assert.h>

template <class T>
class Pile
{

    private:
    //Pile(const Pile&); // on pourrait préférer mettre le constructeur par copie privé.
    
    class Cellule
    {
      public:
        Cellule(const T& e, Cellule* c);
        T contenu;
        Cellule* suivante;
    };

    Cellule* sommet;
    int nb_cellules = 0;

  public:
    Pile() : nb_cellules(0) , sommet(NULL) {};
    Pile(const Pile&);
    ~Pile();

    T& tete();
    void empiler(const T&);
    void depiler(T& out);  // Depiler et copier le sommet dans out.
    T depiler();
    bool contient(const T&) const;
    bool contient(const Cellule*,T&) const;
    bool vide() const { return sommet==NULL;}
    void vider();

    const Pile<T>& operator = (const Pile<T>&);
};

#include "assert.h"
#include "pile.h"

template <class T>
Pile<T>::~Pile()
{
    vider();
}

template <class T>
Pile<T>::Pile(const Pile<T>& autre)
{
    if (autre.sommet == nullptr)
        return;
    else {
        Cellule **ps = &sommet;
        Cellule *it = autre.sommet;

        while(it) {
            *ps = new Cellule(it->contenu,nullptr);
            ps = &((*ps)->suivante);
            it = it->suivante;
        }
    }
}

template <class T>
void Pile<T>::vider()
{
   while (sommet != nullptr) {
       depiler();
   }
}

template <class T>
Pile<T>::Cellule::Cellule(const T& e, Cellule* c)
 : suivante(c)
{
    contenu=e;
}

template <class T>
T& Pile<T>::tete() {
    return sommet->contenu;
}

template <class T>
void Pile<T>::empiler(const T& e)
{
    sommet = new Cellule(e, sommet);
    nb_cellules++;
    assert(sommet);
}

template <class T>
T Pile<T>::depiler()
{
    assert(sommet != nullptr);
    T element = sommet->contenu;
    Cellule* anciensommet = sommet;
    sommet = sommet->suivante;
    delete anciensommet;
    nb_cellules--;
    return element;
}

template <class T>
bool Pile<T>::contient(const T& e) const {

    if (sommet == nullptr)
        return false;
    Cellule *iter = sommet;
    if (iter->contenu == e)
        return true;
    else {
        iter = iter->suivante;
        for(;iter && iter != sommet ; iter = iter->suivante) 
            if (iter->contenu == e) 
                return true;
    }
    return false;

}

// Ne pas oublier nb_cellules a modifier !!!!
template <class T>
const Pile<T>& Pile<T>::operator = (const Pile<T>& autre)
{
   if(this == &autre) return *this;
    vider();
    if (autre.sommet != nullptr) {
        sommet = new Cellule(autre.sommet->contenu, nullptr);
        Cellule *cp = autre.sommet;
        Cellule *c = sommet;
        while(cp->suivante != nullptr) {
            c->suivante = new Cellule(cp->contenu, nullptr);
            c = c->suivante;
            cp = cp->suivante;
        }
    }
    return *this;
}

#endif