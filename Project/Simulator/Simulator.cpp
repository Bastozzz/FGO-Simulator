//
// Created by Bife on 17/01/2023.
//
#include "Simulator.h"
#include <algorithm>
#include <filesystem>

using namespace std;

static const size_t MAX_PARTY_SIZE = 3;

static void notImplemented() {
    clearScreen();
    cout << endl << "Not yet implemented" << endl << endl << endl;
}

int Simulator::normalBattle(int record, int mainQuest, int section, int arrow) {
    //Main quests
    //Fuyuki - Section 1 - Arrow 1
    if(record == 1 && mainQuest == 1 && section == 1 && arrow == 1){
        //Creation of the party
        vector<Servant*> Party = chooseServants();
        if(Party.empty())
            return 0;

        //Creation of the enemy forces
        vector<Enemy*> Enemies;
        for(const string name : {"Skeleton(Saber)", "Skeleton(Saber)"}) {
            Enemy *e = Enemy::loadFromFile(name);
            if(e == nullptr) {
                for(Servant *s : Party) delete s;
                for(Enemy *en : Enemies) delete en;
                waitForEnter();
                return 0;
            }
            Enemies.push_back(e);
        }

        //Group them up and create the battle! (the battle deletes everything when it ends)
        Battle B(Party, Enemies, new Battlefield());
        return B.fight() ? 1 : 0;
    }
    notImplemented();
    return 0;
}

int Simulator::startSim() {
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
        cout << "4 - Exit" << endl;
        cout << "-> ";

        char prompt = readKey();
        if(prompt == '1') {
            cout << endl << endl << "1 - Fuyuki - Singularity F" << endl;
            cout << "2 - Orleans - First Singularity" << endl;
            cout << "-> ";
            prompt = readKey();
            if(prompt == '1'){
                cout << endl << endl << "1 - Section 1" << endl;
                cout << "2 - Section 2" << endl;
                cout << "-> ";
                prompt = readKey();
                if(prompt == '1')
                    normalBattle(1, 1, 1, 1);
                else
                    notImplemented();
            }
            else
                notImplemented();
        }
        else if(prompt == '2' || prompt == '3')
            notImplemented();
        else if(prompt == '4')
            return 1;
        else{
            clearScreen();
            cout << endl << "Select the option you want again" << endl;
        }
    }
}

vector<string> Simulator::listServants() {
    vector<string> names;
    error_code ec;
    for(const auto &entry : filesystem::directory_iterator(dataPath("Servants"), ec)) {
        if(!entry.is_regular_file() || entry.path().extension() != ".txt")
            continue;
        string name = entry.path().stem().string();
        if(name != "FORMAT")
            names.push_back(name);
    }
    sort(names.begin(), names.end());
    return names;
}

vector<Servant*> Simulator::chooseServants() {
    vector<Servant*> Party;
    vector<string> available = listServants();

    cout << endl << "Ready for the battle, choose up to " << MAX_PARTY_SIZE << " servants" << endl
         << "(type 'list' to see them, 'done' to start the battle, 'exit' to go back)" << endl;

    while(Party.size() < MAX_PARTY_SIZE){
        cout << "Servant " << Party.size() + 1 << " -> ";
        string prompt = readLine();

        if(prompt == "list"){
            for(size_t i = 0; i < available.size(); i++)
                cout << i + 1 << " - " << available[i] << endl;
            continue;
        }
        if(prompt == "exit"){
            for(Servant *s : Party) delete s;
            Party.clear();
            clearScreen();
            return Party;
        }
        if(prompt == "done"){
            if(Party.empty())
                cout << "You need at least one servant" << endl;
            else
                break;
            continue;
        }
        if(prompt.empty())
            continue;

        //The player can write the number from the list or the name of the file
        string name = prompt;
        if(all_of(prompt.begin(), prompt.end(), ::isdigit)) {
            size_t n = stoul(prompt);
            if(n >= 1 && n <= available.size())
                name = available[n - 1];
        }

        Servant *s = Servant::loadFromFile(name);
        if(s == nullptr)
            cout << "There isn't such a character named " << prompt << endl;
        else {
            Party.push_back(s);
            cout << s->getName() << " joined the party!" << endl;
        }
    }
    return Party;
}
