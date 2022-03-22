
/*  AUTEUR(S):
    1) Nadir Hadji - HADN08069703
*/

#include "date.h"
#include <cstdio>
#include <iomanip>
#include <assert.h>

Date::Date() : annee(2000), mois(0), jour(1) {}
Date::Date(int a, int m, int j) : annee(a), mois(m), jour(j) {};

void Date::modifier_date(int a, int m, int j) 
{
    annee = a;
    mois = m;
    jour = j;
}

bool Date::operator < (const Date& autre) const
{
    int difference = difference_entre_dates(autre);
    return difference < 0;
}

bool Date::est_valide(const Date& date_courrante) {
    Date debut;
    if (! est_coherente(*this) )
    {
        ERREUR_DATE_INCOHERENTE();
        return false;
    }
    else if ( (*this) < debut) 
    {
        ERREUR_DATE_MINIMUM();
        return false;
    }
    else if ((*this) < date_courrante) {
        ERREUR_DATE_ANTERIEUR();
        return false;
    }
    return true;
}

bool Date::est_coherente(const Date& date) const {

    if ( ! ( DATE_MINIMUM <= date.annee )  )
        return false;
    if (! (1 <= date.mois && date.mois <= 12) )
        return false;
    if (! (1 <= date.jour && date.jour <= 31) )
        return false;
    if ( (date.jour == 31 ) && (date.mois == 2 || date.mois==4 || date.mois==6 || date.mois==9 || date.mois==11) )
        return false;
    if ( (date.jour==30) && (date.mois==2) )
        return false;
    if ( (date.mois==2) && (date.jour==29) && (date.annee % 4 != 0 ) )
        return false;
    if ( (date.mois == 2) && (date.jour == 29) && (date.annee % 400 == 0 ) )
        return true;
    if ( (date.mois == 2 ) && (date.jour == 29) && (date.annee % 100 == 0 ) )
        return false; 
    if ( (date.mois == 2) && (date.jour == 29 ) && (date.annee % 4 == 0 ) )
            return true;
    return true;
}

long int Date::convertir_en_jours(const Date& date) const {
    long int total = date.annee * 365 + date.jour;
    for (int i = 0; i < date.mois - 1; i++)
        total += nb_jours_mois[i];
    total += compter_annee_bissextile(date);
    return total;
}

int Date::compter_annee_bissextile(const Date& date) const
{
    int a = date.annee;
    if ( date.mois <= 2)
        a--;
    return a / 4 - a / 100 + a / 400;
}

int Date::difference_entre_dates(const Date& autre) const
{
    long int total_autre = convertir_en_jours(autre);
    long int total_courrant = convertir_en_jours(*this);
    return (total_courrant - total_autre);
}

std::ostream& operator << (std::ostream& os, const Date& d){
    char chaine[40];
    sprintf(chaine, "%04d-%02d-%02d", d.annee, d.mois, d.jour);
    os << chaine;
    return os;
}

std::istream& operator >> (std::istream& is, Date& d){
    int a=0, m=0, j=0;
    char t1=0,t2=0;
    is >> a >> t1 >> m >> t2 >> j;
    assert(t1=='-');
    assert(t2=='-');
    d.modifier_date(a,m,j);
    return is;
}

