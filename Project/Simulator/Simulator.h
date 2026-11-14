//
// Created by Bife on 17/01/2023.
//

#ifndef FGO_SIM_SIMULATOR_H
#define FGO_SIM_SIMULATOR_H
#include "../Utils/utils.h"
#include "../Battle/Battle.h"
#include <iostream>
#include <string>
#include <vector>

class Simulator {

public:
    Simulator() = default;
    int startSim();
    static int normalBattle(int record, int mainQuest, int section, int arrow);
    //int customBattle();

    // Lets the player choose up to 3 servants. Returns an empty vector if the player gives up
    static vector<Servant*> chooseServants();
    // Names of every servant file in CHARACTERS/Servants
    static vector<string> listServants();
};


#endif //FGO_SIM_SIMULATOR_H
