/*  INF3105 - Structures de données et algorithmes       *
 *  UQAM / Département d'informatique                    *
 *  Automne 2017 / TP1                                   *
 *  http://ericbeaudry.uqam.ca/INF3105/tp1/              */

#include <assert.h>
#include <math.h>
#include "pointst.h"

#define PI 3.14159265359
#define RAYON_TERRE 6371 * 1000  // en mètres

PointST::PointST(const PointST& point)
  : latitude(point.latitude), longitude(point.longitude)
{
}

PointST::PointST(double latitude_, double longitude_) 
  : latitude(latitude_), longitude(longitude_)
{
}

double PointST::distance(const PointST& point) const {
  double s1 = sin((point.latitude-latitude)/2);
  double s2 = sin((point.longitude-longitude)/2);
  return 2*RAYON_TERRE * asin(sqrt(s1*s1 + cos(latitude)*cos(point.latitude)*s2*s2));
}

std::ostream& operator << (std::ostream& os, const PointST& point) {
  os << "(" 
     << (point.latitude * 180.0 / PI)
     << "," 
     << (point.longitude * 180.0 / PI)
     << ")";
  return os;
}

std::istream& operator >> (std::istream& is, PointST& point) {
  char po, vir, pf;
  is >> po;
  if(is){
    is >> point.latitude >> vir >> point.longitude >> pf;
    assert(po=='(');
    assert(vir==',');
    assert(pf==')');
    point.latitude  *= PI / 180.0;
    point.longitude *= PI / 180.0;
  }
  return is;
}


