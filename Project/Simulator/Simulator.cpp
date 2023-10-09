//
// Created by Bife on 17/01/2023.
//
#include "Simulator.h"

using namespace std;

int Simulator::normalBattle(int record, int mainQuest, int section, int arrow) {
    //Main quests
    if(record == 1){
        //Fuyuki
        if(mainQuest == 1){
            if(section == 1){
                if(arrow == 1){
                    //Creation of the party
                    vector<Servant*> Party = chooseServants();

                    //Creation of the enemy forces
                    vector<Enemy*> Enemies;
                    Enemies.push_back(getEnemy("Skeleton(Saber)"));
                    Enemies.push_back(getEnemy("Skeleton(Saber)"));

                    //Creation of the Battlefield
                    Battlefield * Stage = new Battlefield();

                    //Group them up and create the battle!
                    Battle * B = new Battle(Party, Enemies, Stage);
                    B->fight();
                    return 1;
                }
            }
        }
    }
    return 1;
}

int Simulator::startSim() {
    normalBattle(1, 1, 1, 1);
    cout << " ________  ________   ________          ________   ___   _____ ______      \n"
            "|\\  _____\\|\\   ____\\ |\\   __  \\        |\\   ____\\ |\\  \\ |\\   _ \\  _   \\    \n"
            "\\ \\  \\__/ \\ \\  \\___| \\ \\  \\|\\  \\       \\ \\  \\___|_\\ \\  \\\\ \\  \\\\\\__\\ \\  \\   \n"
            " \\ \\   __\\ \\ \\  \\  ___\\ \\  \\\\\\  \\       \\ \\_____  \\\\ \\  \\\\ \\  \\\\|__| \\  \\  \n"
            "  \\ \\  \\_|  \\ \\  \\|\\  \\\\ \\  \\\\\\  \\       \\|____|\\  \\\\ \\  \\\\ \\  \\    \\ \\  \\ \n"
            "   \\ \\__\\    \\ \\_______\\\\ \\_______\\        ____\\_\\  \\\\ \\__\\\\ \\__\\    \\ \\__\\\n"
            "    \\|__|     \\|_______| \\|_______|       |\\_________\\\\|__| \\|__|     \\|__|\n"
            "                                          \\|_________|                     \n"
            "                                                                           \n";
    cout << "Welcome to the FGO Simulator!" << endl;
    for(;;) {
        cout << "1 - Main Record 1" << endl;
        cout << "2 - Chaldea Gate" << endl;
        cout << "3 - Custom Battle" << endl;
        cout << "3 - Exit" << endl;
        cout << "->" << " ";

        string prompt;
        cin >> prompt;
        if(prompt == "1") {
            cout << endl << endl << "1 - Fuyuki - Singularity F" << endl;
            cout << "2 - Orleans - First Singularity" << endl;
            cout << "->";
            cin >> prompt;
            if(prompt == "1"){
                cout << endl << endl << "1 - Section 1" << endl;
                cout << "2 - Section 2" << endl;
                cout << "->";
                cin >> prompt;
                if(prompt == "1"){
                    normalBattle(1, 1, 1, 1);
                }
                else if(prompt == "2") {
                    system("cls");
                    cout << endl << "Not yet implemented" << endl << endl << endl;
                }
            }
            else if(prompt == "2") {
                system("cls");
                cout << endl << "Not yet implemented" << endl << endl << endl;
            }
        }
        else if(prompt == "2") {
            system("cls");
            cout << endl << "Not yet implemented" << endl << endl << endl;
        }
        else if(prompt == "3")
            return 1;
        else{
            system("cls");
            cout << endl << "Select the option you want again" << endl;
        }
    }
}

vector<Servant*> Simulator::chooseServants() {
    vector<Servant*> Party;
    int nServants;
    cout << endl << "Ready for the battle, choose your servants" << endl << "(you can list them by typing 'list')" << endl << "-> ";
    for(;;){
        string prompt;
        cin >> prompt;
        if(prompt == "list"){
            cout << "2 - Artoria(Saber)" << endl;
            cout << "->";
        }
        else if(prompt == "exit")
            exit(0);
        else{
            if(prompt == "2")
                prompt = "Artoria(Saber)";
            ostringstream oss;
            oss << "../CHARACTERS/Servants/" << prompt << ".txt";

            //Will read the file where the enemy is
            ifstream file(oss.str());
            if(file.fail()) {
                cout << "There isn't such a character named " << prompt << endl << endl << "->";
            }
            else {
                //Will read every line of the file
                string info[17];
                for (int i = 0; i < 17; i++) {
                    file >> info[i];
                }
                try {
                    if (info[1].size() > 8 || stoi(info[2]) < 0 || stoi(info[3]) < 0 || stoi(info[4]) < 0 || stoi(info[5]) < 0 || stoi(info[7]) < 0 ||
                        stoi(info[9]) < 0 || stod(info[10]) < 0 || stod(info[11]) < 0 || stod(info[12]) < 0 || stod(info[13]) < 0 || info[15].size() != 5 || stoi(info[16]) < 0)
                        throw 1;
                }
                catch (...) {
                    cout << "There was an error reading the file of the servant " << prompt;
                    exit(-1);
                }
                //Servant here
                Servant *s = new Servant(&info[0], &info[1], stoi(info[2]), stoi(info[3]), stoi(info[4]), stoi(info[5]), &info[6], stoi(info[7]), &info[8],
                                         stoi(info[9]), stod(info[10]), stod(info[11]),stod(info[12]), stod(info[13]), &info[14], &info[15], stoi(info[16]));
                Party.push_back(s);
                break;
            }
        }
    }
    return Party;
}



Enemy * Simulator::getEnemy(string name) {
    ostringstream oss;
    oss << "../CHARACTERS/Enemies/" << name << ".txt";

    //Will read the file where the enemy is
    ifstream file(oss.str());
    if(file.fail()) {
        cout << "THERE ISNT A CHARACTER NAMED " << name << endl << endl;
        return nullptr;
    }

    //Will read every line of the file
    string info[11];
    for(int i = 0; i < 11; i++){
        file >> info[i];
    }
    try{
        if(stoi(info[1]) < 0 || stoi(info[2]) < 0 || stoi(info[3]) < 0 || stoi(info[6]) < 0 || stoi(info[7]) < 0 || stoi(info[8]) < 0 || stoi(info[9]) < 0)
            throw 1;
    }
    catch(...){
        cout << "There was an error reading the file of the enemy " << name;
        exit(-1);
    }
    Enemy * a = new Enemy(&info[0], stoi(info[1]), stoi(info[2]), stoi(info[3]), &info[4], &info[5], stoi(info[6]), stoi(info[7]), stoi(info[8]), stoi(info[9]), &info[10]);
    return a;
}

