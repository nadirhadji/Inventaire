#include <fstream>
#include <string.h>
#include "arbremap.h"
using namespace std;

class inventaire
{
private:
    ArbreMap<string,ArbreMap<string,int>> map; 

public:
    inventaire(/* args */) {}
    ~inventaire() {}
};