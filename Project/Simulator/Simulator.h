//
// Created by Bife on 17/01/2023.
//

#ifndef FGO_SIM_SIMULATOR_H
#define FGO_SIM_SIMULATOR_H
#include "../Utils/utils.h"
#include "../Battle/Battle.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <csignal>

class Simulator {

public:
    Simulator() = default;
    int startSim();
    static int normalBattle(int record, int mainQuest, int section, int arrow);
    //int customBattle();

    static vector<Servant*> chooseServants();
    static Enemy * getEnemy(string name);
};


#endif //FGO_SIM_SIMULATOR_H
