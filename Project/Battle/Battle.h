//
// Created by Bife on 17/01/2023.
//

#ifndef FGO_SIM_BATTLE_H
#define FGO_SIM_BATTLE_H
#include "../Servant/Servant.h"
#include "../Enemy/Enemy.h"
#include "../Battlefield/Battlefield.h"
#include <chrono>
#include <thread>

class Battle {
    int TURN;
    int STAGE;
    int TARGET;

    vector<Servant*> Party;
    vector<Enemy*> Enemies;
    Battlefield * Stage;

    vector<Card*> CardsOnPlay;
    vector<Card*> Combo;
public:
    Battle(vector<Servant*> P, vector<Enemy*> E, Battlefield * S);
    ~Battle();

    void fight();
    void attack();
    void damagePhase();
    void checkdeath();
    void changeTarget(int t);

    void addToCombo(Card *C);

    void showStage();
    static void showOptions();
    static void printLine();

    void showCards();

    void orderCards();

};


#endif //FGO_SIM_BATTLE_H
