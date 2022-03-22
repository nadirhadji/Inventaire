/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2017 | TP2
    http://ericbeaudry.ca/INF3105/tp2/
*/
#include "date.h"
#include <sstream>
#include <vector> // std::vecteur est permis uniquement pour ce programme test.

int main()
{
    std::cout << "Vérification de la classe Date" << std::endl;
    std::stringstream str("1999-01-01 1999-01-02 1999-01-31 1999-12-01 1999-12-31 2016-12-01 2017-01-02 2017-02-01 2017-04-15 2017-05-04 2017-06-01 2017-10-17");
    std::vector<Date> dates;
    while(!str.eof()){
        Date d;
        str >> d >> std::ws;
        std::cout << d << std::endl;
        if(str) dates.push_back(d);
    }
    
    // Test du comparateur
    for(unsigned int i=0;i<dates.size();i++)
        for(unsigned int j=0;j<dates.size();j++){
             if(i<j){
                 if(!(dates[i]<dates[j]))
                     std::cout << "Erreur : dates[" << i << "]<dates[" << j << "] : " << dates[i] << "<" << dates[j] << " retourne faux!" << std::endl;
             }else if(j<i){
                 if(!(dates[j]<dates[i]))
                     std::cout << "Erreur : dates[" << j << "]<dates[" << i << "] : " << dates[j] << "<" << dates[i] << " retourne faux!" << std::endl;
             }else{ // i==j
                 if(dates[j]<dates[i])
                     std::cout << "Erreur : dates[" << j << "]<dates[" << i << "] : " << dates[j] << "<" << dates[i] << " retourne faux!" << std::endl;
             }
        }
    std::cout << " --- FIN ---" << std::endl;
    return 0;
}

