#if !defined(_MAGASIN__H_)
#define _MAGASIN__H_

#include <fstream>
#include <string.h>
#include "../point/pointst.h"
using namespace std;

class Magasin {

    public:
        Magasin();
        Magasin(const Magasin&);
        Magasin(string&, PointST&);
        Magasin(const string&);
        ~Magasin();
        void operator =  ( const Magasin& );
        bool operator <  ( const Magasin& ) const;
        bool operator >  ( const Magasin& ) const;
        bool operator == ( const Magasin& ) const;

    private:
        string nom;
        PointST position;   
    
    friend class Recommandation;
    friend class Data;
};

#endif