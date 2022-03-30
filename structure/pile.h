/*  INF3105 | Structures de données et algorithmes
 *  UQAM | Département d'informatique | Automne 2017
 *  Pile pour les intérateur d'Arbre AVL pour le Lab6 et TP2
 *  http://ericbeaudry.ca/INF3105/
 */
#if !defined(__PILE__H__)
#define __PILE__H__

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
    Pile();
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
Pile<T>::Pile()
{
    sommet = NULL;
    nb_cellules = 0;
}

template <class T>
Pile<T>::~Pile()
{
    vider();
}

template <class T>
Pile<T>::Pile(const Pile<T>& autre)
{
    Cellule **ps = &sommet; //pointeur vers le pointeur de sommet;
    Cellule *iterateur = autre.sommet;

    while(iterateur) {
      *ps = new Cellule(iterateur->contenu, nullptr);
      ps = &((*ps)->suivante);
      iterateur = iterateur->suivante;
    }
    nb_cellules = autre.nb_cellules;
}

template <class T>
void Pile<T>::vider()
{
    while( ! vide() )
        depiler();
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
    assert(sommet != NULL);
    Cellule c(*sommet);
    delete sommet;
    nb_cellules--;
    sommet = c.suivante;
    return c.contenu;
}

template <class T>
void Pile<T>::depiler(T& e)
{
    assert(sommet!=NULL);
    e = sommet->contenu;
    Cellule* c = sommet;
    sommet = sommet->suivante;
    delete c;
    nb_cellules--;
}

template <class T>
bool Pile<T>::contient(const T& e) const {

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
    if(&autre == this) 
        return *this;
    
    Cellule** t = &sommet;
    Cellule* a = autre.sommet;
    while(a){
        if((*t) == NULL)
             *t = new Cellule(a->contenu, NULL);
        else
             (*t)->contenu = a->contenu;
    
        t = &((*t)->suivante);
        a = a->suivante;
    }
    a = *t;
    *t = NULL;
    while(a!=NULL){
        Cellule* temp = a->suivante;
        delete a;
        a = temp;
    }

    return *this;
}

#endif

