//
// Created by Bife on 17/01/2023.
//

#ifndef FGO_SIM_BATTLE_H
#define FGO_SIM_BATTLE_H
#include "../Servant/Servant.h"
#include "../Enemy/Enemy.h"
#include "../Battlefield/Battlefield.h"
#include <random>

// A Battle owns the servants, enemies and battlefield it receives
// and deletes them when it is destroyed.
class Battle {
    int TURN;
    int STAGE;
    size_t TARGET;

    vector<Servant*> Party;
    vector<Enemy*> Enemies;
    Battlefield * Stage;

    vector<Card*> CardsOnPlay;
    vector<Card*> Combo;

    mt19937 rng;

public:
    Battle(vector<Servant*> P, vector<Enemy*> E, Battlefield * S);
    ~Battle();

    Battle(const Battle &) = delete;
    Battle &operator=(const Battle &) = delete;

    // Runs the battle until the player wins or leaves. Returns true on victory
    bool fight();

private:
    void attack();
    void chooseSkills();

    void damagePhase();
    void checkdeath();
    void changeTarget(size_t t);
    void retargetIfDead();

    void addToCombo(Card *C);
    void resetCardOrders();

    void showStage();
    static void showOptions();
    static void printLine();

    void showCards();
    void showSkills();

    void orderCards();
    size_t checkHowManyEnemies() const;

    static void victoryScreen();
};


#endif //FGO_SIM_BATTLE_H
