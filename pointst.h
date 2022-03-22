/*  INF3105 - Structures de données et algorithmes       *
 *  UQAM / Département d'informatique                    *
 *  Automne 2017 / TP1                                   *
 *  http://ericbeaudry.uqam.ca/INF3105/tp1/              */

#if !defined(_POINTST__H_)
#define _POINTST__H_

#include <iostream>

// Cette classe représente un point sur la surface de la Terre.
class PointST {

  public:
    PointST(){}
    PointST(double latitude_, double longitude_);
    PointST(const PointST&);

    double distance(const PointST&) const;

  private:
    double latitude;
    double longitude;

  friend std::ostream& operator << (std::ostream&, const PointST&);
  friend std::istream& operator >> (std::istream&, PointST&);
};

#endif

