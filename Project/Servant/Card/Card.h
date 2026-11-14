//
// Created by Bife on 17/01/2023.
//

#ifndef FGO_SIM_CARD_H
#define FGO_SIM_CARD_H

#include <iostream>
#include <string>

using namespace std;
class Servant;

class Card {
    string TYPE;
    Servant * servantAttached;
    int CURRENT_CRIT_STARS;

    int selectionOrder; // 0 = not selected, 1..3 = position in the chain

public:
    Card(string t, Servant * s);

    void setOrder(int i);

    int getOrder() const;
    string getType() const;
    Servant * getServantAttached() const;
};


#endif //FGO_SIM_CARD_H
