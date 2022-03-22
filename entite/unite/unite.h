#include <string.h>
#include "../date/date.h"
using namespace std;

class Unite
{
private:
    string nom;
    Date date_expiration;

public:
    Unite(/* args */);
    ~Unite();
    bool operator == (const Unite& u) const;
};


