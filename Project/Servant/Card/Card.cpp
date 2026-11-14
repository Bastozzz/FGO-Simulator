//
// Created by Bife on 17/01/2023.
//

#include "Card.h"

#include <utility>

Card::Card(string t, Servant * s):TYPE(std::move(t)), servantAttached(s), CURRENT_CRIT_STARS(0), selectionOrder(0){}

//If order is 0, it is not selected
void Card::setOrder(int i) {
    selectionOrder = i;
}

int Card::getOrder() const {
    return selectionOrder;
}

string Card::getType() const {
    return TYPE;
}

Servant *Card::getServantAttached() const {
    return servantAttached;
}
