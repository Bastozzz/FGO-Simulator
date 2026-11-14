//
// Created by Bife on 17/01/2023.
//

#include "Battle.h"
#include "../Utils/utils.h"
#include <algorithm>

// The game shows at most 3 enemies at the same time
static const size_t MAX_ENEMIES_ON_FIELD = 3;
static const size_t CELL_WIDTH = 58;

Battle::Battle(vector<Servant*> P, vector<Enemy*> E, Battlefield * S)
    : TURN(1), STAGE(1), TARGET(0), Party(std::move(P)), Enemies(std::move(E)), Stage(S), rng(random_device{}()) {}

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

bool Battle::fight() {
    clearScreen();
    cout << "The fight is about to begin! (Knowledge is power)" << endl << endl;
    for(size_t i = 0; i < Party.size(); i++)
        cout << i + 1 << " - " << Party[i]->getName() << " | Level:" << Party[i]->getLvl() << endl;

    cout << endl << "vs" << endl << endl;

    for(auto & Enemy : Enemies)
        cout << Enemy->getName() << " | Level:" << Enemy->getLvl() << endl;

    waitForEnter();

    changeTarget(0);
    orderCards();

    //Start the fight
    for(;;){
        showStage();
        showOptions();
        char c = readKey();
        if(c == '1')
            chooseSkills();
        else if(c == '2')
            attack();
        else if(c == '3'){
            clearScreen();
            cout << "You exited the battle" << endl;
            return false;
        }
        //Choose next target
        else if(c == 's')
            changeTarget(TARGET + 1);
        //Choose target before
        else if(c == 'w' && TARGET > 0)
            changeTarget(TARGET - 1);

        if(checkHowManyEnemies() == 0){
            victoryScreen();
            return true;
        }
    }
}

void Battle::attack() {
    Combo.clear();
    resetCardOrders();

    const size_t cardsToChoose = min<size_t>(3, CardsOnPlay.size());
    while(Combo.size() < cardsToChoose) {
        showStage();
        showCards();
        cout << endl << endl << "1-5: choose card | e: undo last card | w/s: change target | c: cancel" << endl << "-> ";
        char c = readKey();

        if(c >= '1' && c <= '5') {
            size_t index = c - '1';
            if(index < CardsOnPlay.size() && CardsOnPlay[index]->getOrder() == 0)
                addToCombo(CardsOnPlay[index]);
        }
        //Undo the last chosen card
        else if(c == 'e') {
            if(!Combo.empty()) {
                Combo.back()->setOrder(0);
                Combo.pop_back();
            }
        }
        //Go back without attacking
        else if(c == 'c') {
            resetCardOrders();
            Combo.clear();
            return;
        }
        //Choose next target
        else if(c == 's')
            changeTarget(TARGET + 1);
        //Choose target before
        else if(c == 'w' && TARGET > 0)
            changeTarget(TARGET - 1);
    }

    showStage();
    damagePhase();
    checkdeath();
    waitForEnter();

    resetCardOrders();
    Combo.clear();
    TURN++;
    orderCards();
}

void Battle::chooseSkills(){
    showStage();
    showSkills();
    waitForEnter("Skills aren't implemented yet. Press Enter to go back...");
}

void Battle::damagePhase() {
    uniform_real_distribution<double> randomModifier(0.9, 1.1);
    cout << endl;

    //Card damage
    for(Card *card : Combo){
        //If the target died with the previous card, attack the next enemy alive
        retargetIfDead();
        if(Enemies[TARGET]->isDead())
            break;

        //CALCULATE THE DAMAGE FROM CLASS
        //CALCULATE THE DAMAGE FROM CLASS ADVANTAGE
        //CALCULATE THE CRIT DAMAGE
        double cardValue = 1.0;
        if(card->getType() == "Buster")
            cardValue = 1.5;
        else if(card->getType() == "Arts")
            cardValue = 1.0;
        else if(card->getType() == "Quick")
            cardValue = 0.8;

        Servant *s = card->getServantAttached();
        int damage = (int)(s->getAtk() * 0.23 * cardValue * randomModifier(rng));
        Enemy *target = Enemies[TARGET];
        target->takeDamage(damage);

        cout << "  " << s->getAKA() << " - " << card->getType() << " -> " << target->getName()
             << ": " << damage << " damage" << (target->isDead() ? " (defeated)" : "") << endl;
    }
}

void Battle::checkdeath() {
    for(auto it = Enemies.begin(); it != Enemies.end(); ){
        if((*it)->isDead()){
            delete *it;
            it = Enemies.erase(it);
        }
        else
            ++it;
    }
    if(TARGET >= min(Enemies.size(), MAX_ENEMIES_ON_FIELD))
        changeTarget(0);
}

size_t Battle::checkHowManyEnemies() const {
    return Enemies.size();
}

void Battle::changeTarget(size_t t) {
    if(t < Enemies.size() && t < MAX_ENEMIES_ON_FIELD)
        TARGET = t;
}

void Battle::retargetIfDead() {
    if(!Enemies[TARGET]->isDead())
        return;
    for(size_t i = 0; i < Enemies.size() && i < MAX_ENEMIES_ON_FIELD; i++)
        if(!Enemies[i]->isDead()) {
            TARGET = i;
            return;
        }
}

void Battle::addToCombo(Card *C) {
    Combo.push_back(C);
    C->setOrder((int)Combo.size());
}

void Battle::resetCardOrders() {
    for(Card *c : CardsOnPlay)
        c->setOrder(0);
}


void Battle::showStage() {
    clearScreen();
    cout << " Turn " << TURN << endl;
    cout << " " << string(CELL_WIDTH * 2 + 1, '-') << endl;
    //Print the first lines
    printLine();

    //For each 3 characters
    for(size_t i = 0; i < 3; i++){
        string servantCell, enemyCell, hpCell;

        //This will show the servants one by one
        if(Party.size() > i)
            servantCell = "     " + Party[i]->getName() + " | Level:" + to_string(Party[i]->getLvl());

        //This will show the enemies one by one with level
        if(Enemies.size() > i) {
            enemyCell = "     " + Enemies[i]->getName() + " | Level:" + to_string(Enemies[i]->getLvl()) + " | Rank:" + Enemies[i]->getRank();
            hpCell = (TARGET == i ? " ->  HP:" : "     HP:") + to_string(Enemies[i]->getHp());
        }

        cout << "|" << padRight(servantCell, CELL_WIDTH) << "|" << padRight(enemyCell, CELL_WIDTH) << "|" << endl;
        //WILL SHOW THE CHARGES
        cout << "|" << padRight("", CELL_WIDTH) << "|" << padRight(hpCell, CELL_WIDTH) << "|" << endl;

        //Print the spaces between characters
        for(int l = 0; l < 2; l++)
            printLine();

        if(i < 2){
            cout << "|     ------------------------------------------------     |     -------------------------------------------------    |" << endl;
            printLine();
        }
    }
    cout << " " << string(CELL_WIDTH * 2 + 1, '-') << endl;
}

void Battle::showOptions() {
    cout << "             _____ _    _ _ _                                                           _   _             _    \n"
            "            / ____| |  (_) | |                                                     /\\  | | | |           | |   \n"
            "           | (___ | | ___| | |___                                                 /  \\ | |_| |_ __ _  ___| | __\n"
            "            \\___ \\| |/ / | | / __|                                               / /\\ \\| __| __/ _` |/ __| |/ /\n"
            "            ____) |   <| | | \\__ \\                                              / ____ \\ |_| || (_| | (__|   < \n"
            "           |_____/|_|\\_\\_|_|_|___/                                             /_/    \\_\\__|\\__\\__,_|\\___|_|\\_\\\n";
    cout << endl << "1: skills | 2: attack | 3: exit battle | w/s: change target" << endl << "-> ";
}

void Battle::printLine() {
    cout << "|" << string(CELL_WIDTH, ' ') << "|" << string(CELL_WIDTH, ' ') << "|" << endl;
}

void Battle::showCards() {
    cout << "                  ";
    for(size_t i = 0; i < CardsOnPlay.size(); i++)
        cout << "___________       ";
    cout << endl;
    for(int i = 0; i < 6; i++){
        cout << "                 ";
        for(Card *card : CardsOnPlay){
            if(i == 1)
                cout << "|  " << padRight(card->getServantAttached()->getAKA(), 9) << "|     ";
            else if(i == 4)
                cout << "|  " << padRight(card->getOrder() == 0 ? "" : to_string(card->getOrder()), 9) << "|     ";
            else if(i == 5)
                cout << "|  " << padRight(card->getType(), 9) << "|     ";
            else
                cout << "|           |     ";
        }
        cout << endl;
    }
    cout << "                  ";
    for(size_t i = 0; i < CardsOnPlay.size(); i++)
        cout << "-----------       ";
}

void Battle::showSkills(){
    cout << endl;
    for(Servant *s : Party) {
        cout << s->getName() << ":" << endl;
        const vector<string> &skills = s->getSkillNames();
        if(skills.empty())
            cout << "   (no skills)" << endl;
        for(size_t i = 0; i < skills.size(); i++)
            cout << "   " << i + 1 << " - " << skills[i] << endl;
    }
}

void Battle::victoryScreen(){
    clearScreen();
    cout << "\n\n\n\n\n\n\n\n########.......##...######################################......#######...####.###....###.####...######.####...###.\n"
            ".###..####....###...##.#########.#######.####.....####...#.......##....#..###..#####..##...###.###...##..###...###.\n"
            ".###..###....#####......###.##...####....###......###..#.........##...#...###..######.##...###.#####.....###...###.\n"
            ".#######.....#..##......##.......###.....###.......#####........#######...###..##..#####...###...######..#########.\n"
            ".###..###...#######....###.......####....###....#..##..#........###...#...###..##...####...###.#....####.###...###.\n"
            ".###...###.##....###...###........##.....###...##..##....##.....####......###..##....###...###..#....###.###...###.\n"
            ".###...##..##....####..###.......####....#######..########......####......###..##..........##....#####...###...##..\n"
            ".#######................................................................................................#####.####.\n";
    waitForEnter();
    clearScreen();
}

void Battle::orderCards() {
    // Temporary: deal 5 random cards from all the party's cards.
    // The real FGO deck (15 cards, reshuffled every 3 turns) comes in a later phase.
    vector<Card*> all;
    for(Servant *s : Party)
        for(Card *c : s->getCards())
            all.push_back(c);
    shuffle(all.begin(), all.end(), rng);
    if(all.size() > 5)
        all.resize(5);
    CardsOnPlay = all;
}
