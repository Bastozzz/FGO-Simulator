//
// Created by Bife on 17/01/2023.
//

#ifndef FGO_SIM_ENEMY_H
#define FGO_SIM_ENEMY_H
#include <iostream>
#include <string>
using namespace std;

class Enemy {
    string NAME;
    int LVL;
    int HP;
    int ATTACK;
    string RANK;
    string ATTRIBUTE;
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
    Enemy(const string &n, int lv, int h, int a, const string &r, const string &attri, int c, int act, int crit_c, int death, const string &gen);

    // Reads an enemy from CHARACTERS/Enemies/<fileName>.txt
    // Returns nullptr if the file doesn't exist or is badly formatted
    static Enemy *loadFromFile(const string &fileName);

    void takeDamage(int dmg);
    bool isDead() const;

    string getName() const;
    int getLvl() const;
    int getHp() const;
    string getRank() const;
};
#endif //FGO_SIM_ENEMY_H
