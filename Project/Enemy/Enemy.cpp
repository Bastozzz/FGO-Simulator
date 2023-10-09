//
// Created by Bife on 17/01/2023.
//

#include "Enemy.h"
Enemy::Enemy(const string * n, int lv, int h, int a, const string * r, const string * attri,
             int c, int act, int crit_c, int death, const string * gen):
             NAME(*n), LVL(lv), HP(h), ATTACK(a), RANK(*r), /*Attributes, */ CHARGES(c), ACTIONS(act),
             CRIT_CHANCE(crit_c), DEATH_RATE(death), GENDER(*gen), CURRENT_HP(h), CURRENT_CHARGES(0){}


void Enemy::takeDamage(int dmg) {
    CURRENT_HP -= dmg;
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

