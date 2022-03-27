/*  AUTEUR(S):
    1) Nadir HAdji - HADN08069703
*/

#if !defined(__DATE_H__)
#define __DATE_H__

#include <iostream>

#define DATE_MINIMUM 2000

#define ERREUR_DATE_MINIMUM() \
  std::cout << "Erreur DATE : la date saise est inferieur au 2000-01-01;\n" << std::endl; \
  std::cout << "Opération annulée" << std::endl;

#define ERREUR_DATE_ANTERIEUR() \
  std::cout << "Erreur DATE : la date saisie est inferieur a la date courante" << std::endl; \
  std::cout << "Operation annulée" << std::endl;

#define ERREUR_DATE_INCOHERENTE()\
  std::cout << "Erreur DATE : la date saisie n'existe pas dans le calandrier" << std::endl; \
  std::cout << "Operation annulée" << std::endl;

const int nb_jours_mois[12]
    = { 31, 28, 31, 30, 31, 30,
       31, 31, 30, 31, 30, 31 };

class Date{
  public:
    Date();
    Date(int,int,int);
    bool modifier(const Date&);
    bool est_modifiable_par(const Date& date);
    bool operator == (const Date& date) const;
    bool operator < (const Date& date) const;
    bool operator <= (const Date& date) const;
    void operator = (const Date& date);

  private:
    int annee;
    int mois;
    int jour;
    bool est_coherente(const Date& date) const;
    long int convertir_en_jours(const Date& date) const;
    int compter_annee_bissextile(const Date& date) const;
    int difference_entre_dates(const Date& autre) const;
    friend std::ostream& operator << (std::ostream&, const Date& date);
    friend std::istream& operator >> (std::istream&, Date& date);
};

#endif
