//
// Created by Bife on 17/01/2023.
//

#ifndef FGO_SIM_CARD_H
#define FGO_SIM_CARD_H

#include <iostream>
using namespace std;
class Servant;

class Card {
    string TYPE;
    int CURRENT_CRIT_STARS;

    int selectionOrder;
    Servant * servantAttached;
public:
    Card(){};
    Card(string t, Servant * s);

    void setOrder(int i);

    int getOrder();
    string getType();
    Servant * getServantAttached();
};


#endif //FGO_SIM_CARD_H
