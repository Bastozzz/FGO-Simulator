//
// Created by Bife on 17/01/2023.
//

#include "Servant.h"
#include "../Utils/utils.h"

Servant::Servant(const string &n, const string &ak, int i, int lv, int h, int a, const string &attri, int c, const string &curve,
                 int sAbs, double sGen, double npChAtt, double npChDef, double death, const string &gen, const string &cards,
                 const string &hits, const vector<string> &skills)
                 :NAME(n), AKA(ak), ID(i), LVL(lv), HP(h), ATK(a), ATTRIBUTE(attri), COST(c), CURVE(curve), STAR_ABSORB(sAbs),
                 STAR_GEN(sGen), NP_CHARGE_ATTACK(npChAtt), NP_CHARGE_DEF(npChDef), DEATH_RATE(death), GENDER(gen),
                 HITS(hits), SKILL_NAMES(skills), CURRENT_HP(h), CURRENT_NPCHARGE(0){
    for(char card : cards){
        if(card == 'B')
            DECK.push_back(new Card("Buster", this));
        else if(card == 'A')
            DECK.push_back(new Card("Arts", this));
        else if(card == 'Q')
            DECK.push_back(new Card("Quick", this));
    }
}

Servant::~Servant() {
    for(Card *c : DECK)
        delete c;
    DECK.clear();
}

Servant *Servant::loadFromFile(const string &fileName) {
    vector<string> info;
    if(!readLines(dataPath("Servants/" + fileName + ".txt"), info))
        return nullptr;

    // 17 lines of stats + 3 skill names (see FORMAT.txt)
    if(info.size() < 17) {
        cout << "The file of the servant " << fileName << " has missing lines" << endl;
        return nullptr;
    }
    try {
        int id = stoi(info[2]), lvl = stoi(info[3]), hp = stoi(info[4]), atk = stoi(info[5]), cost = stoi(info[7]);
        int starAbsorb = stoi(info[9]);
        double starGen = stod(info[10]), npAtk = stod(info[11]), npDef = stod(info[12]), death = stod(info[13]);

        if(info[1].size() > 8 || id < 0 || lvl < 0 || hp < 0 || atk < 0 || cost < 0 || starAbsorb < 0 ||
           starGen < 0 || npAtk < 0 || npDef < 0 || death < 0 || info[15].size() != 5 || info[16].size() != 4)
            throw invalid_argument("invalid value");

        vector<string> skills;
        for(size_t i = 17; i < info.size() && skills.size() < 3; i++)
            if(!info[i].empty())
                skills.push_back(info[i]);

        return new Servant(info[0], info[1], id, lvl, hp, atk, info[6], cost, info[8], starAbsorb, starGen,
                           npAtk, npDef, death, info[14], info[15], info[16], skills);
    }
    catch(const exception &) {
        cout << "There was an error reading the file of the servant " << fileName << endl;
        return nullptr;
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
const vector<string> &Servant::getSkillNames() const {
    return SKILL_NAMES;
}
const vector<Card*> &Servant::getCards() const {
    return DECK;
}
