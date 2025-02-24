//
// Created by Bife on 17/01/2023.
//

#ifndef FGO_SIM_ENEMY_H
#define FGO_SIM_ENEMY_H
#include <iostream>
using namespace std;

class Enemy {
    string NAME;
    int LVL;
    int HP;
    int ATTACK;
    string RANK;
    //ATTRIBUTE;
    int CHARGES;
    int ACTIONS;
    int CRIT_CHANCE;
    int DEATH_RATE;
    string GENDER;

    //vector<string> ALLIGNMENT;
    //vector<string> BASIC_TRAITS;
    //vector<Hit> HITS

    //vector<Enemy_Skill> SKILLS;
    //vector<Enemy

    //Current fight stats
    int CURRENT_HP;
    int CURRENT_CHARGES;

public:
    Enemy(const string * n, int lv, int h, int a, const string * r, const string * attri, int c, int act, int crit_c, int death, const string * gen);

    void takeDamage(int dmg);
    void test();

    string getName() const;
    int getLvl() const;
    int getHp() const;
    string getRank() const;
};
#endif //FGO_SIM_ENEMY_H
