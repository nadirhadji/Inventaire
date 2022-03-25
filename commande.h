#if !defined(_COMMANDE__H_)
#define _COMMANDE__H_

#include <string>
#include <iostream>
#include "./structure/arbremap.h"
using namespace std;

class Commande{
  public:
    // À compléter
  private:
    // À compléter
    friend istream& operator >> (istream& is, Commande& c);
};

#endif