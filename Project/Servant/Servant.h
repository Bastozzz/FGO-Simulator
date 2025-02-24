//
// Created by Bife on 17/01/2023.
//
#ifndef FGO_SIM_SERVANT_H
#define FGO_SIM_SERVANT_H

#include "Card/Card.h"
#include "Skill/Skill.h"
#include <iostream>
#include <vector>
using namespace std;

class Servant {
    string NAME;
    string AKA;
    int ID;
    int LVL;
    int HP;
    int ATK;
    //ATTRIBUTE
    int COST;
    string CURVE;
    int STAR_ABSORB;
    double STAR_GEN;
    double NP_CHARGE_ATTACK;
    double NP_CHARGE_DEF;
    double DEATH_RATE;
    string GENDER;

    //vector<string> ALLIGNMENT;
    //vector<string> BASIC_TRAITS;
    vector<Card*> DECK;
    vector<Skill*> SKILLS;
    //vector<Passive_Skill> PASSIVE_SKILLS;
    //vector<Append_Skill> APPEND_SKILLS;
    //Noble_Phantasm * NP;

    //Stats of the current fight
    int CURRENT_HP;
    int CURRENT_NPCHARGE;

public:
    Servant(const string *n, const string *ak, int i, int LVL, int h, int a, const string *attri, int c, const string *curve,
            int sAbs, double sGen, double npChAtt, double npChDef, double death, const string *gen, const string *cards, int hits);

    string getName() const;
    string getAKA() const;
    int getLvl() const;
    int getAtk() const;
    vector<Card*> getCards();
};
#endif //FGO_SIM_SERVANT_H
