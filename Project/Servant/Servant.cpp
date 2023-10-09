//
// Created by Bife on 17/01/2023.
//

#include "Servant.h"

Servant::Servant(const string *n, const string *ak, int i, int lv, int h, int a, const string *attri, int c, const string *curve,
                 int sAbs, double sGen, double npChAtt, double npChDef, double death, const string *gen, const string *cards, int hits)
                 :NAME(*n), AKA(*ak), ID(i), LVL(lv), HP(h), ATK(a), /*Attribute,*/ COST(c), CURVE(*curve), STAR_ABSORB(sAbs),
                 STAR_GEN(sGen), NP_CHARGE_ATTACK(npChAtt), NP_CHARGE_DEF(npChDef), DEATH_RATE(death), GENDER(*gen),
                 CURRENT_HP(h), CURRENT_NPCHARGE(0){
                     for(int i = 0; i < 5; i++){
                        if(cards->at(i) == 'B'){
                            Card * C = new Card("Buster", this);
                            DECK.push_back(C);
                        }
                        else if(cards->at(i) == 'A'){
                            Card * C = new Card("Arts", this);
                            DECK.push_back(C);
                        }
                        else if(cards->at(i) == 'Q'){
                            Card * C = new Card("Quick", this);
                            DECK.push_back(C);
                        }
                     }
                 }



string Servant::getName() const{
    return NAME;
}
string Servant::getAKA() const {
    return AKA;
}
int Servant::getLvl() const {
    return LVL;
}
int Servant::getAtk() const {
    return ATK;
}
vector<Card*> Servant::getCards() {
    return DECK;
}

