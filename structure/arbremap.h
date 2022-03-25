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
using namespace std;

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

        class Iterateur;

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
                Iterateur(ArbreMap& a) : iter(a.entrees.debut()) {}
                Iterateur(typename ArbreAVL<Entree>::Iterateur i) : iter(i){}
                operator bool() const; 
                Iterateur& operator++();
                const K& cle() const;
                V& valeur();

            private:
                typename ArbreAVL<Entree>::Iterateur iter;
        };        
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
    typename ArbreAVL<Entree>::Iterateur iter = entrees->debut();
    while(iter) {

    }

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
void ArbreMap<K,V>::enlever(const K& cle)
{
    if ( entrees->contient(cle) ) {
        typename ArbreAVL<Entree>::Iterateur iter = entrees->rechercher(cle);
        delete (*entrees)[iter];
    }
}

template <class K, class V>
bool ArbreMap<K,V>::contient(const K& c) const
{
    return entrees->contient(Entree(c));
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
    typename ArbreAVL<Entree>::Iterateur iter = entrees->rechercher(c);
    return (*entrees)[iter].valeur;
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
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercher(const K& cle) 
{ 
    return Iterateur(entrees->rechercher(cle));
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercherEgalOuSuivant(const K& cle) 
{
    return Iterateur(entrees->rechercherEgalOuSuivant(cle));
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercherEgalOuPrecedent(const K& cle) 
{
    return Iterateur(entrees->rechercherEgalOuPrecedent(cle));
}

//---------------IMPLEMENTATION ITERATEUR -----------------------

template <class K, class V>
ArbreMap<K,V>::Iterateur::operator bool() const 
{
    return iter.operator bool();
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur& ArbreMap<K,V>::Iterateur::operator++() 
{
    ++iter; 
    return *this;
}

template <class K, class V>
const K& ArbreMap<K,V>::Iterateur::cle() const 
{
    return (*iter).cle;
}

template <class K, class V>
V& ArbreMap<K,V>::Iterateur::valeur() {
    return (V&) (*iter).valeur;
}

#endif
