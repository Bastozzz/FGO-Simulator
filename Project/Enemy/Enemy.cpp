//
// Created by Bife on 17/01/2023.
//

#include "Enemy.h"
#include "../Utils/utils.h"
#include <stdexcept>

Enemy::Enemy(const string &n, int lv, int h, int a, const string &r, const string &attri,
             int c, int act, int crit_c, int death, const string &gen):
             NAME(n), LVL(lv), HP(h), ATTACK(a), RANK(r), ATTRIBUTE(attri), CHARGES(c), ACTIONS(act),
             CRIT_CHANCE(crit_c), DEATH_RATE(death), GENDER(gen), CURRENT_HP(h), CURRENT_CHARGES(0){}

Enemy *Enemy::loadFromFile(const string &fileName) {
    vector<string> info;
    if(!readLines(dataPath("Enemies/" + fileName + ".txt"), info)) {
        cout << "There isn't an enemy named " << fileName << endl;
        return nullptr;
    }
    if(info.size() < 11) {
        cout << "The file of the enemy " << fileName << " has missing lines" << endl;
        return nullptr;
    }
    try {
        int lvl = stoi(info[1]), hp = stoi(info[2]), atk = stoi(info[3]);
        int charges = stoi(info[6]), actions = stoi(info[7]), crit = stoi(info[8]), death = stoi(info[9]);
        if(lvl < 0 || hp < 0 || atk < 0 || charges < 0 || actions < 0 || crit < 0 || death < 0)
            throw invalid_argument("invalid value");
        return new Enemy(info[0], lvl, hp, atk, info[4], info[5], charges, actions, crit, death, info[10]);
    }
    catch(const exception &) {
        cout << "There was an error reading the file of the enemy " << fileName << endl;
        return nullptr;
    }
}

void Enemy::takeDamage(int dmg) {
    CURRENT_HP -= dmg;
    if(CURRENT_HP < 0)
        CURRENT_HP = 0;
}
bool Enemy::isDead() const {
    return CURRENT_HP <= 0;
}
string Enemy::getName() const {
    return NAME;
}
int Enemy::getLvl() const {
    return LVL;
}
int Enemy::getHp() const {
    return CURRENT_HP;
}
string Enemy::getRank() const {
    return RANK;
}
