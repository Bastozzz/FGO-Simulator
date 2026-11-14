//
// Created by Bife on 17/01/2023.
//
#ifndef FGO_SIM_SERVANT_H
#define FGO_SIM_SERVANT_H

#include "Card/Card.h"
#include "Skill/Skill.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Servant {
    string NAME;
    string AKA;
    int ID;
    int LVL;
    int HP;
    int ATK;
    string ATTRIBUTE;
    int COST;
    string CURVE;
    int STAR_ABSORB;
    double STAR_GEN;
    double NP_CHARGE_ATTACK;
    double NP_CHARGE_DEF;
    double DEATH_RATE;
    string GENDER;
    string HITS; // Hits per card type, e.g. "2213" = Quick, Arts, Buster, Extra

    //vector<string> ALLIGNMENT;
    //vector<string> BASIC_TRAITS;
    vector<Card*> DECK;
    vector<string> SKILL_NAMES;
    //vector<Passive_Skill> PASSIVE_SKILLS;
    //vector<Append_Skill> APPEND_SKILLS;
    //Noble_Phantasm * NP;

    //Stats of the current fight
    int CURRENT_HP;
    int CURRENT_NPCHARGE;

public:
    Servant(const string &n, const string &ak, int i, int lv, int h, int a, const string &attri, int c, const string &curve,
            int sAbs, double sGen, double npChAtt, double npChDef, double death, const string &gen, const string &cards,
            const string &hits, const vector<string> &skills);
    ~Servant();

    // A servant owns its cards, so it can't be copied
    Servant(const Servant &) = delete;
    Servant &operator=(const Servant &) = delete;

    // Reads a servant from CHARACTERS/Servants/<fileName>.txt (see FORMAT.txt)
    // Returns nullptr if the file doesn't exist or is badly formatted
    static Servant *loadFromFile(const string &fileName);

    string getName() const;
    string getAKA() const;
    int getLvl() const;
    int getAtk() const;
    const vector<string> &getSkillNames() const;
    const vector<Card*> &getCards() const;
};
#endif //FGO_SIM_SERVANT_H
