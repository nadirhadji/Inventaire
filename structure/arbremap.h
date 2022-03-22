/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2017 | Lab8 + TP2
    http://ericbeaudry.uqam.ca/INF3105/lab8/
    http://ericbeaudry.uqam.ca/INF3105/tp2/

    AUTEUR(S):
     (1) Nom + Code permanent du l'étudiant.e 1
     (2) Nom + Code permanent du l'étudiant.e 2
*/
#if !defined(_ARBREMAP___H_)
#define _ARBREMAP___H_

#include "arbreavl.h"
using namespace std;

template <class K, class V>
class ArbreMap
{
  private:
    class Entree{
        public:
            Entree(const K& c):cle(c),valeur(){}
            K cle;
            V valeur;
            bool operator < (const Entree& e) const { return cle < e.cle; }
            bool operator > (const Entree& e) const { return cle > e.cle; }
    };

    ArbreAVL<Entree> *entrees;

  public:

    ArbreMap();
    ArbreMap(const ArbreMap<K,V>&);
    ~ArbreMap();
    bool contient(const K&) const;
    void inserer(const K&, const V&);
    void enlever(const K&);
    void vider();
    bool vide() const;
    const V& operator[] (const K&) const;
    V& operator[] (const K&);
};

template <class K, class V>
ArbreMap<K,V>::ArbreMap() {
    entrees = new ArbreAVL<Entree>();
}

template <class K, class V>
ArbreMap<K,V>::ArbreMap(const ArbreMap<K,V>& autre) {
    if (entrees == nullptr)
        entrees = new ArbreAVL<Entree>(autre);
    else if (entrees != autre.entrees) {
        entrees->vider();
        delete entrees;
        entrees = new ArbreAVL<Entree>(autre);
    }
}

template <class K, class V>
ArbreMap<K,V>::~ArbreMap() {
    cout << "Supression de la Map" << endl;
    delete entrees;
    entrees = nullptr;
}

template <class K, class V>
void ArbreMap<K,V>::vider(){
    if ( ! entrees->vide() )
        entrees->vider();
}

template <class K, class V>
bool ArbreMap<K,V>::vide() const{
    return entrees->vide();
}

template <class K, class V>
void ArbreMap<K,V>::inserer(const K& cle, const V& valeur) {
    if (entrees != nullptr) {
        Entree e(cle);
        e.valeur = valeur;
        entrees->inserer(e);
    }
}

template <class K, class V>
void ArbreMap<K,V>::enlever(const K& c)
{
    // À compléter
}

template <class K, class V>
bool ArbreMap<K,V>::contient(const K& c) const
{
    if ( entrees != nullptr)
        return entrees->contient(c);
    return false;
}

template <class K, class V>
const V& ArbreMap<K,V>::operator[] (const K& c)  const
{
    typename ArbreAVL<Entree>::Iterateur iter = entrees->rechercher(c);
    return (*entrees)[iter].valeur;
}

template <class K, class V>
V& ArbreMap<K,V>::operator[] (const K& c) 
{
    typename ArbreAVL<Entree>::Iterateur iter = entrees->rechercher(Entree(c));
    if(!iter) {
        entrees->inserer(Entree(c));
        iter = entrees->rechercher(c);
    }
    return (*entrees)[iter].valeur;
}

#endif
