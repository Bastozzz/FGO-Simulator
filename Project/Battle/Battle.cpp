//
// Created by Bife on 17/01/2023.
//

#include <conio.h>
#include "Battle.h"

Battle::Battle(vector<Servant*> P, vector<Enemy*> E, Battlefield * S):Party(std::move(P)), Enemies(std::move(E)), TURN(1), STAGE(1){}

Battle::~Battle() {
    //This will delete everything so the memory is freed
    for(auto & i : Party)
        delete i;
    Party.clear();
    for(auto & Enemie : Enemies)
        delete Enemie;
    Enemies.clear();
    delete Stage;
}

void Battle::fight() {
    srand (time(NULL));
    system("cls");
    cout << "The fight is about to begin! (Knowledge is power)" << endl << endl;
    for(auto & i : Party)
        cout << "1 - " << i->getName() << " | Level:" << i->getLvl() << endl;
    //SHOW STATS

    cout << endl << "vs" << endl << endl;

    for(auto & Enemy : Enemies)
        cout << Enemy->getName() << " | Level:" << Enemy->getLvl() << endl;
    //SHOW LEVEL

    changeTarget(0);

    //this_thread::sleep_for(3s);

    //Start the fight
    for(;;){
        //PASS TURNS
        showStage();
        showOptions();
        orderCards();
        char c = getchar();
        if(c == '1')
            chooseSkills();
        else if(c == '2')
            attack();
        else if(c == '3'){
            system("cls");
            cout << "You exited the battle" << endl;
            break;
        }
            //Choose next target
        else if(c == 's' || c == 'S'){
            if(TARGET < 2 && TARGET < Enemies.size()-1) changeTarget(TARGET + 1);
        }
            //Choose target before
        else if(c == 'w' || c == 'W') {
            if (TARGET > 0) changeTarget(TARGET - 1);
        }
        if(checkHowManyEnemies() == 0){
            victoryScreen();
            break;
        }
    }
    cout << endl << "-------------------------------------------" << endl;
    //The fight has ended
    delete this;
}

void Battle::attack() {
    Combo.clear();
    for(int i = 0; i < 3; i++) {
        showStage();
        showCards();
        char c;
        cin.get(c);

        if (c == '1' && CardsOnPlay[0]->getOrder() == 0)
            addToCombo(CardsOnPlay[0]);
        else if (c == '2' && CardsOnPlay[1]->getOrder() == 0)
            addToCombo(CardsOnPlay[1]);
        else if (c == '3' && CardsOnPlay[2]->getOrder() == 0)
            addToCombo(CardsOnPlay[2]);
        else if (c == '4' && CardsOnPlay[3]->getOrder() == 0)
            addToCombo(CardsOnPlay[3]);
        else if (c == '5' && CardsOnPlay[4]->getOrder() == 0)
            addToCombo(CardsOnPlay[4]);
        else if (c == '6') {
            system("cls");
            cout << "You exited the battle" << endl;
            break;
        }
        else if(c == 'e' || c == 'E'){
            CardsOnPlay[i]->setOrder(0);
            return;
        }

        //Choose next target
        else if(c == 's' || c == 'S'){
            if(TARGET < 2 && TARGET < Enemies.size()-1){
                changeTarget(TARGET + 1);
                i--;
            }
        }
        //Choose target before
        else if(c == 'w' || c == 'W') {
            if (TARGET > 0) {
                changeTarget(TARGET - 1);
                i--;
            }
        }
        else
            i--;
    }

    damagePhase();
    showStage();
    //this_thread::sleep_for(3s);
    checkdeath();
    for(int i = 0; i < 5; i++)
        CardsOnPlay[i]->setOrder(0);
}

void Battle::chooseSkills(){
    system("cls");
    showStage();
    showSkills();

    getch();
}

void Battle::damagePhase() {
    //Card damage
    for(int i = 0; i < 3; i++){
        int r = rand() %  20 + 90;
        double randomModifier = (double)r / 100 ;
        //CALCULATE THE DAMAGE FROM CLASS
        //CALCULATE THE DAMAGE FROM CLASS ADVANTAGE
        //CALCULATE THE CRIT DAMAGE
        //TARGET CHANGES IF CHARACTER CARD CHANGES
        if(Combo[i]->getType() == "Buster")
            Enemies[TARGET]->takeDamage(Combo[i]->getServantAttached()->getAtk() * 0.23 * randomModifier * 1.5);
        else if(Combo[i]->getType() == "Arts")
            Enemies[TARGET]->takeDamage(Combo[i]->getServantAttached()->getAtk() * 0.23 * randomModifier * 1.0);
        else if(Combo[i]->getType() == "Quick")
            Enemies[TARGET]->takeDamage(Combo[i]->getServantAttached()->getAtk() * 0.23 * randomModifier * 0.8);
    }
}

void Battle::checkdeath() {
    for(int e = 0; e < Enemies.size(); e++){
        cout << Enemies[e]->getHp();
        if(Enemies[e]->getHp() <= 0){
            delete Enemies[e];
            Enemies.erase(Enemies.begin()+e);
            changeTarget(0);
        }
    }
}

int Battle::checkHowManyEnemies() {
    return (Enemies.size());
}


void Battle::changeTarget(int t) {
    TARGET = t;
}

void Battle::addToCombo(Card *C) {
    Combo.push_back(C);
    C->setOrder(Combo.size());
}



void Battle::showStage() {
    system("cls");
    cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
    //Print the first lines
    printLine();

    //For each 3 characters
    for(int i = 0; i < 3; i++){
        //This will show the servants one by one
        if(Party.size() > i) {
            cout << "|     " << Party[i]->getName() << " | " << "Level:" << Party[i]->getLvl();
            for(int l = 0; l < 59 - (15 + Party[i]->getName().size() + Party[i]->getLvl()%10); l++)
                cout << " ";
        }
        else{
            cout << "|";
            for(int l = 0; l < 58; l++)
                cout << " ";
        }

        //This will show the enemies one by one with level
        if(Enemies.size() > i) {
            cout << "|     " << Enemies[i]->getName() << " | Level:" << Enemies[i]->getLvl() << " | Rank:" << Enemies[i]->getRank();
            for(int l = 0; l < 59 -(23 + Enemies[i]->getName().size() + Enemies[i]->getLvl()%10 + Enemies[i]->getRank().size()); l++)
                cout << " ";
            cout << "|" << endl;
        }
        else{
            cout << "|";
            for(int l = 0; l < 58; l++)
                cout << " ";
            cout << "|" << endl;
        }

        //WILL SHOW THE CHARGES
        //Will show the enemy stats
        if(TARGET == i && Enemies.size() > i){
            cout << "|";
            for(int l = 0; l < 58; l++)
                cout << " ";
            cout << "| ->  HP:" << Enemies[i]->getHp();
            for(int l = 0; l < 47 - Enemies[i]->getHp()%10; l++)
                cout << " ";
            cout << "|" << endl;
        }
        else if(Enemies.size() > i){
            cout << "|";
            for(int l = 0; l < 58; l++)
                cout << " ";
            cout << "|     HP:" << Enemies[i]->getHp();
            for(int l = 0; l < 47 - Enemies[i]->getHp()%10; l++)
                cout << " ";
            cout << "|" << endl;
        }
        else
            printLine();

        //Print the spaces between characters
        for(int i = 0; i < 2; i++)
            printLine();

        if(i < 2){
            cout << "|     ------------------------------------------------     |     -------------------------------------------------    |" << endl;
            printLine();
        }
    }
    cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
}

void Battle::showOptions() {
    cout << "             _____ _    _ _ _                                                           _   _             _    \n"
            "            / ____| |  (_) | |                                                     /\\  | | | |           | |   \n"
            "           | (___ | | ___| | |___                                                 /  \\ | |_| |_ __ _  ___| | __\n"
            "            \\___ \\| |/ / | | / __|                                               / /\\ \\| __| __/ _` |/ __| |/ /\n"
            "            ____) |   <| | | \\__ \\                                              / ____ \\ |_| || (_| | (__|   < \n"
            "           |_____/|_|\\_\\_|_|_|___/                                             /_/    \\_\\__|\\__\\__,_|\\___|_|\\_\\\n";
    cout << endl << "Press 1 to check skills, or 2 to Attack or 3 to exit simulation";
}

void Battle::printLine() {
    cout << "|";
    for(int l = 0; l < 58; l++)
        cout << " ";
    cout << "|";
    for(int l = 0; l < 58; l++)
        cout << " ";
    cout << "|" << endl;
}

void Battle::showCards() {
    cout << "                  ";
    for(int i = 0; i < 5; i++)
        cout << "___________       ";
    cout << endl;
    for(int i = 0; i < 6; i++){
        cout << "                 ";
        for(int j = 0; j < 5; j++){
            if(i == 1){
                cout << "|  " << CardsOnPlay[j]->getServantAttached()->getAKA();
                for(int n = 0; n < 9 - CardsOnPlay[j]->getServantAttached()->getAKA().size(); n++)
                    cout << " ";
                cout << "|     ";
            }
            else if(i == 4){
                cout << "|  ";
                if(CardsOnPlay[j]->getOrder() == 0)
                    cout << " ";
                else{
                    cout << CardsOnPlay[j]->getOrder();
                }
                for(int n = 0; n < 8; n++)
                    cout << " ";
                cout << "|     ";
            }
            else if(i == 5){
                cout << "|  " << CardsOnPlay[j]->getType();
                for(int n = 0; n < 9 - CardsOnPlay[j]->getType().size(); n++)
                    cout << " ";
                cout << "|     ";
            }
            else
                cout << "|           |     ";
        }
        if(i == 1)
            cout << "Use 1 to 5";
        else if(i == 2)
            cout << "to select";
        else if(i == 3)
            cout << "the cards:";
        cout << endl;
    }
    cout << "                  ";
    for(int i = 0; i < 5; i++)
        cout << "-----------       ";
}

void Battle::showSkills(){

}

void Battle::victoryScreen(){
    system("cls");
    cout << "\n\n\n\n\n\n\n\n########.......##...######################################......#######...####.###....###.####...######.####...###.\n"
            ".###..####....###...##.#########.#######.####.....####...#.......##....#..###..#####..##...###.###...##..###...###.\n"
            ".###..###....#####......###.##...####....###......###..#.........##...#...###..######.##...###.#####.....###...###.\n"
            ".#######.....#..##......##.......###.....###.......#####........#######...###..##..#####...###...######..#########.\n"
            ".###..###...#######....###.......####....###....#..##..#........###...#...###..##...####...###.#....####.###...###.\n"
            ".###...###.##....###...###........##.....###...##..##....##.....####......###..##....###...###..#....###.###...###.\n"
            ".###...##..##....####..###.......####....#######..########......####......###..##..........##....#####...###...##..\n"
            ".#######................................................................................................#####.####.";
    getch();
    system("cls");
}

void Battle::orderCards() {
    //Maybe put the 15 cards of the decks inside the vector and then make a random to get them
    CardsOnPlay = Party[0]->getCards();
}

