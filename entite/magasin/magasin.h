#if !defined(_MAGASIN__H_)
#define _MAGASIN__H_

#include <fstream>
#include <string.h>
#include "../point/pointst.h"
using namespace std;

class Magasin
{
private:
    string nom_magasin;
    PointST position_magasin;
    
public:
    Magasin();
    Magasin( const string&, const PointST&);
    Magasin(const Magasin& autre);
    Magasin(string&);
    ~Magasin();
    void operator = (const Magasin*);
    void operator = (const Magasin&);
    bool operator == (const Magasin&) const;
    bool operator < (const Magasin&) const;
    bool operator > (const Magasin&) const;
    const string& nom() const;
    const PointST& position() const;
};

#endif