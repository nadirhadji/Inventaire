/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2017 | Lab8 + TP2
    http://ericbeaudry.uqam.ca/INF3105/lab8/
    http://ericbeaudry.uqam.ca/INF3105/tp2/
    AUTEUR(S):
     (1) Nadir Hadji - HADN080697
*/
#if !defined(_ARBREMAP___H_)
#define _ARBREMAP___H_

#include "arbreavl.h"

template <class K, class V>
class ArbreMap
{
    class Entree
    {
        public:
            Entree(const K& c):cle(c),valeur(){}
            K cle;
            V valeur;
            bool operator < (const Entree& e) const { return cle < e.cle; }
            bool operator > (const Entree& e) const { return cle > e.cle; }
    };

    ArbreAVL<Entree> entrees;

    public:

        class Iterateur;
        
        bool contient(const K&) const;
        void vider();
        bool vide() const;

        Iterateur debut();
        Iterateur fin();
        Iterateur rechercher(const K& cle);
        Iterateur rechercherEgalOuSuivant(const K& cle);
        Iterateur rechercherEgalOuPrecedent(const K& cle);

        const V& operator[] (const K&) const;
        V& operator[] (const K&);

        V& operator[](const Iterateur& iter);
        const V& operator[](const Iterateur& iter) const ;

    public: 

        class Iterateur
        {
            public:
                Iterateur(ArbreMap<K,V>& a) : iter(a.entrees.debut()) {}
                Iterateur(const ArbreMap<K,V>& a) : iter(a.entrees.debut()) {}
                Iterateur(typename ArbreAVL<Entree>::Iterateur i) : iter(i){}
                operator bool() const { return iter.operator bool(); }
                Iterateur& operator++() { ++iter; return *this; }
                const K& cle() const { return (*iter).cle; }
                const V& valeur() { return (V&) (*iter).valeur; }

            private:
                typename ArbreAVL<Entree>::Iterateur iter;
        };        
};

template <class K, class V>
bool ArbreMap<K,V>::contient(const K& c) const
{
    return entrees.contient(Entree(c));
}

template <class K, class V>
void ArbreMap<K,V>::vider() {
    if(! entrees.vide())
        entrees.vider();
}

template <class K, class V>
bool ArbreMap<K,V>::vide() const {
    //assert(entrees);
    return entrees.vide();
}

//Utiliser seulement lorsque l'element existe sinon crash
template <class K, class V>
const V& ArbreMap<K,V>::operator[] (const K& c)  const
{
    typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(c);
    return entrees[iter].valeur;
}

template <class K, class V>
V& ArbreMap<K,V>::operator[] (const K& c) 
{
    typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(c);
    if (!iter) {
        entrees.inserer(c);
        iter = entrees.rechercher(Entree(c));
    }
    return entrees[iter].valeur;
}

template <class K, class V>
V& ArbreMap<K,V>::operator[] (const Iterateur& iter) 
{
    return (V&) (*iter).valeur;
}

template <class K, class V>
const V& ArbreMap<K,V>::operator[](const Iterateur& iter) const {
    return (*iter).valeur;
}

//---------------IMPLEMENTATION ARBREMAP ------------------------
template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::debut() 
{ 
    return Iterateur(*this); 
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::fin() 
{ 
    return Iterateur(entrees.fin());
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercher(const K& c) 
{ 
    return Iterateur(entrees.rechercher(c));
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercherEgalOuSuivant(const K& c) 
{
    return Iterateur(entrees->rechercherEgalOuSuivant(c));
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercherEgalOuPrecedent(const K& c) 
{
    return Iterateur(entrees->rechercherEgalOuPrecedent(c));
}

//---------------IMPLEMENTATION ITERATEUR -----------------------

#endif