/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/

#include "date.h"
#include <cstdio>
#include <iomanip>
#include <assert.h>

bool Date::operator <(const Date& d) const{
    return false;
}

std::ostream& operator << (std::ostream& os, const Date& d){
    int a=2017, m=10, j=17; // <<=== utilisez le paramètre d au lieu de 2017-10-17
    char chaine[40];
    sprintf(chaine, "%04d-%02d-%02d", a, m, j);
    os << chaine;
    return os;
}

std::istream& operator >> (std::istream& is, Date& d){
    int a=0, m=0, j=0;
    char t1=0,t2=0;
    is >> a >> t1 >> m >> t2 >> j;
    assert(t1=='-');
    assert(t2=='-');
    // À compléter: transférez les valeur a,m,j dans l'objet d.
    return is;
}

