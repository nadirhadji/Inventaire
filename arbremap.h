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
    };

    ArbreAVL<Entree> entrees;

  public:

    bool contient(const K&) const;
    void enlever(const K&);
    void vider();
    bool vide() const;
    const V& operator[] (const K&) const;
    V& operator[] (const K&);
};

template <class K, class V>
void ArbreMap<K,V>::vider(){
    if ( entrees.racine != nullptr)
        entrees.vider();
}

template <class K, class V>
bool ArbreMap<K,V>::vide() const{
    if ( entrees.racine != nullptr)
        return entrees.vide();
    else
        return false;
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
        return entrees.contient(c);
    return false;
}

template <class K, class V>
const V& ArbreMap<K,V>::operator[] (const K& c)  const
{
    typename ArbreAVL<Entree>::Iterateur iter=entrees.rechercher(c);
    return entrees[iter].valeur;
}

template <class K, class V>
V& ArbreMap<K,V>::operator[] (const K& c) 
{
    typename ArbreAVL<Entree>::Iterateur iter=entrees.rechercher(Entree(c));
    if(!iter) {
        entrees.inserer(Entree(c));
        iter = entrees.rechercher(c);
    }
    return entrees[iter].valeur;
}

#endif
