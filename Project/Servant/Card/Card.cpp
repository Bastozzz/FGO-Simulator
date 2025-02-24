//
// Created by Bife on 17/01/2023.
//

#include "Card.h"

Card::Card(string t, Servant * s):TYPE(t), servantAttached(s),selectionOrder(0){}

//If order is 0, it is not selected
void Card::setOrder(int i) {
    selectionOrder = i;
}

int Card::getOrder() {
    return selectionOrder;
}

string Card::getType() {
    return TYPE;
}

Servant *Card::getServantAttached() {
    return servantAttached;
}
