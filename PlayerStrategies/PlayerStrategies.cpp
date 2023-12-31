#include <vector>
#include "PlayerStrategies.h"
#include "Map.h"
#include "Orders.h"

using namespace std;

HumanPlayerStrategy::HumanPlayerStrategy(Player *player) {
    p = player;
}

vector<Territory *> HumanPlayerStrategy::toAttack() {
    vector<Territory *> attackList;

    for(Territory *t : p->getTerritoryList()){
        for(int i = 0; i < t->getAdjacentTerritories()->size(); i++) {
            Territory *adjacent = t->getAdjacentTerritories()->at(i);

            //check if player owns the territory, if yes break
            if (adjacent->getPlayer()->getID() == p->getID()) {
                continue;
            }
                //check if the territory is already in the attacklist, if yes break
            else {
                bool alreadyInList = false;
                for (Territory *terr: attackList) {
                    if (terr->getName() == adjacent->getName()) {
                        alreadyInList = true;
                        break;
                    }
                }
                if (alreadyInList) {
                    continue;
                } else {
                    attackList.push_back(adjacent);
                }
            }
        }
    }
    return attackList;
}

vector<Territory *> HumanPlayerStrategy::toDefend() {
    return p->getTerritoryList();
}

void HumanPlayerStrategy::issueOrder() {
    //deploy phase
    int territoryIndex, numUnits;

    int tempNum = *(p->getReinforcementPool());

    cout << "Let's start by deploying army units from your reinforcement pool. " << endl;

    while (tempNum > 0){
        cout << "You have " << tempNum << " army units in your reinforcement pool." << endl;

        //print the player's list of territories
        p->printTerritoryList();

        //get user input for which territory they want to deploy armies to
        cout << "Enter the index of territory you wish to deploy army units:";
        territoryIndex = p->getUserTerritoryIndex(toDefend());

        //get user input for num of armies to deploy
        numUnits = p->getUserNum(tempNum);

        tempNum -= numUnits;
        cout << "A Deploy Order of " <<  numUnits << " unit(s) to " << p->getTerritoryList()[territoryIndex]->getName() << " will be issued." << endl;
        auto *deployOrder = new Deploy(p, p->getTerritoryList()[territoryIndex], numUnits);
        p->getOrdersList()->addList(deployOrder);
    }

    cout << "\nGreat, all your reinforcement troops have been deployed." << endl;

    // advance phase
    cout << "Now let's issue Advance orders!" << endl;

    bool playerDone = false;

    while(!playerDone) {
        string playerInput;
        int playerChoice, sourceIndex, targetIndex;

        cout << "Do you wish to issue Advance orders? Enter \"YES\" or \"NO\"" << endl;
        cout << "Any other input would be considerd as \"NO\"" << endl;
        cin >> playerInput;

        if (playerInput == "YES") {
            cout << "Enter \"1\" to defend and \"2\" to attack" << endl;
            cin >> playerChoice;

            if (playerChoice == 1) {
                //print toDefend list
                p->printToDefend();

                //get user source territory
                cout << "Enter the index of the territory you want to move troops from";
                sourceIndex = p->getUserTerritoryIndex(toDefend());

                //get user target territory
                cout << "Enter the index of the territory you want to move troops to";
                targetIndex = p->getUserTerritoryIndex(toDefend());

                //get num of armies to move
                numUnits = p->getUserNum(toDefend()[sourceIndex]->getArmies());

                cout << "An Advance Order of " << numUnits << " army units from " << toDefend()[sourceIndex]->getName() << " to "
                     << toDefend()[targetIndex]->getName() << " will be issued." << endl;
                auto *advanceOrder = new Advance(p, p->toDefend()[sourceIndex], p->toDefend()[targetIndex], numUnits);
                p->getOrdersList()->addList(advanceOrder);

            } else if (playerChoice == 2) {
                p->printTerritoryList();
                p->printToAttack();

                cout << "Enter the index of the territory you want to move troops from";
                sourceIndex = p->getUserTerritoryIndex(toDefend());

                cout << "Enter the index of the territory you want to move troops to";
                targetIndex = p->getUserTerritoryIndex(toAttack());

                numUnits = p->getUserNum(toDefend()[sourceIndex]->getArmies());


                cout << "An Advance Order of " << numUnits << " army units from " << p->getTerritoryList()[sourceIndex]->getName()
                     << " to " << toAttack()[targetIndex]->getName() << " will be issued." << endl;
                auto *advanceOrder = new Advance(p, p->toDefend()[sourceIndex], p->toAttack()[targetIndex], numUnits);
                p->getOrdersList()->addList(advanceOrder);
            }


            else{
                cout << "Invalid choice." << endl;
            }
        }

        else{
            playerDone = true;
        }

    }

    int cardIndex;
    string cardInput;
    bool correctIndex = false;
    if(p->getHand()->getCardNum() == 0) cout << "You do not own any cards" << endl;
    else {
        //Print cards
        cout << "Here are the cards in your hand: " << endl;
        for (int i = 0; i < p->getHand()->getCardNum(); i++) {
            cout << i << "- " << p->getHand()->getCard(i).getTypeAsString() << endl;
        }

        cout << "Do you wish to play a card? Enter \"YES\" or \"NO\"" << endl;
        cout << "Any other input would be considerd as \"NO\"" << endl;
        cin >> cardInput;

        if (cardInput == "YES") {
            while(!correctIndex){
                cout << "Enter the index of the card you want to play:";
                cin >> cardIndex;

                if (cardIndex >= 0 && cardIndex <= p->getHand()->getCardNum())
                    correctIndex = true;
                else {
                    cout << "Invalid index. Please enter another number." << endl;
                }
            }

            p->getHand()->getCard(cardIndex).play(p, p->getDeck());
            p->getDeck()->addCard(p->getHand()->getCard(cardIndex)); //puts it back to the deck
            p->getHand()->removeCard(cardIndex); //removes it from player's hand
        }

    }
}

string HumanPlayerStrategy::getType() {
    return "HUMAN";
}

AggressivePlayerStrategy::AggressivePlayerStrategy(Player *player) {
    p = player;
}

vector<Territory *> AggressivePlayerStrategy::toAttack() {
    vector<Territory *> attackList;

    for (Territory *t: p->getTerritoryList()) {
        for (int i = 0; i < t->getAdjacentTerritories()->size(); i++) {
            Territory *adjacent = t->getAdjacentTerritories()->at(i);

            //check if player owns the territory, if yes break
            if (adjacent->getPlayer()->getID() == p->getID()) {
                continue;
            }
                //check if the territory is already in the attacklist, if yes break
            else {
                bool alreadyInList = false;
                for (Territory *terr: attackList) {
                    if (terr->getName() == adjacent->getName()) {
                        alreadyInList = true;
                        break;
                    }
                }
                if (alreadyInList) {
                    continue;
                } else {
                    attackList.push_back(adjacent);
                }
            }
        }
    }
    return attackList;
}

vector<Territory *> AggressivePlayerStrategy::toDefend() {
    return p->getTerritoryList();
}

void AggressivePlayerStrategy::issueOrder() {
    int reinforcements = *(p->getReinforcementPool());
    vector<Territory *> sortedTerritories = p->getTerritoryList();

    if (sortedTerritories.empty()) {
        cout << "Aggressive player has no territories/orders to make" << endl;
        return;
    }

    sort(sortedTerritories.begin(), sortedTerritories.end(),
         [](Territory *a, Territory *b) {
             return a->getArmies() > b->getArmies();
         }
    );

    for (Territory *t: sortedTerritories) {
        cout << t->getName() << " - " << t->getArmies() << " troop(s)" << endl;
    }

    Territory *strongestTerritory = nullptr;
    Territory *targetTerritory = nullptr;
    for (Territory *t: sortedTerritories) {
        // if the territory is not adjacent to an enemy territory, skip it
        for (Territory *adjacent: *t->getAdjacentTerritories())
            if (adjacent->getPlayer()->getID() != p->getID()) {
                strongestTerritory = t;
                targetTerritory = adjacent;
                break;
            }
        if (targetTerritory == nullptr)
            continue;
    }
    if (targetTerritory == nullptr or strongestTerritory == nullptr) {
        cout << "Aggressive player has no territories/orders to make" << endl;
        return;
    }
    auto *deployOrder = new Deploy(p, strongestTerritory, reinforcements);
    p->getOrdersList()->addList(deployOrder);
    cout << "\t+ Deploy to " << strongestTerritory->getName() <<
         " (" << strongestTerritory->getArmies() + reinforcements << " total)" << endl;
    // advance half of all nearby armies to the territory
    for (Territory *adjacent: *strongestTerritory->getAdjacentTerritories()) {
        if (adjacent->getPlayer()->getID() == p->getID()) {
            if (adjacent->getArmies() == 1)  // skip if there is only one army
                continue;
            auto *advanceOrder = new Advance(p, adjacent, strongestTerritory, adjacent->getArmies() / 2);
            p->getOrdersList()->addList(advanceOrder);
            cout << "\t+ Advance (defend) from " << adjacent->getName() << " to " << strongestTerritory->getName()
                 << endl;
        }
    }

    // advance into target territory
    auto *advanceOrder = new Advance(p, strongestTerritory, targetTerritory, strongestTerritory->getArmies() - 1);
    p->getOrdersList()->addList(advanceOrder);
    cout << "\t+ Advance (attack) from " << strongestTerritory->getName() << " to " << targetTerritory->getName()
         << endl;

    if (p->getHand()->getCardNum() == 0) {
        cout << "Aggressive player has no cards." << endl;
        return;
    }
    // play a bomb card if player has one
    vector<int> usedCards;
    for (int i = 0; i < p->getHand()->getCardNum(); i++) {
        Cards currentCard = p->getHand()->getCard(i);
        // if a card is a bomb, play it
        if (currentCard.getType() == BOMB) {
            cout << "\t+ Playing bomb card on " << targetTerritory->getName() << endl;
            Orders *order = new Bomb(p, targetTerritory);
            p->getOrdersList()->addList(order);
            usedCards.push_back(i);  // add card index to the used cards list
            break;
        }
    }
    // remove used cards from player's hand
    for (const int &i: usedCards) {
        p->getHand()->removeCard(i);
        p->getDeck()->addCard(p->getHand()->getCard(i)); //puts it back to the deck
    }

}

string AggressivePlayerStrategy::getType() {
    return "AGGRESSIVE";
}


BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *player) {
    p = player;
}

vector<Territory *> BenevolentPlayerStrategy::toAttack() {
    vector<Territory *> attackList;
    return attackList; //returns an empty list since cannot attack
}

vector<Territory *> BenevolentPlayerStrategy::toDefend() {
    return p->getTerritoryList();
}

void BenevolentPlayerStrategy::issueOrder() {

    int reinforcements = *(p->getReinforcementPool());
    vector<Territory *> sortedTerritories = p->getTerritoryList();
    sort(sortedTerritories.begin(), sortedTerritories.end(),
         [](Territory *a, Territory *b) {
             return a->getArmies() < b->getArmies();
         });
    map<Territory *, int> pendingReinforcements;

    if (sortedTerritories.empty()) {
        cout << "Benevolent player has no territories/orders to make" << endl;
        return;
    }

    for (Territory *t: sortedTerritories) {
        cout << t->getName() << " - " << t->getArmies() << " troop(s)" << endl;
    }

    while (reinforcements > 0) {
        // Sort the territories based on the original army count plus the pending reinforcements.
        sort(sortedTerritories.begin(), sortedTerritories.end(),
             [&pendingReinforcements](Territory *a, Territory *b) {
                 return (a->getArmies() + pendingReinforcements[a]) < (b->getArmies() + pendingReinforcements[b]);
             }
        );

        Territory *t = sortedTerritories[0];

        // Simulate the deployment by incrementing the pending reinforcements.
        pendingReinforcements[t]++;
        auto *deployOrder = new Deploy(p, t, 1);
        p->getOrdersList()->addList(deployOrder);
        cout << "\t+ Deploy to " << t->getName() << " (" << t->getArmies() + pendingReinforcements[t] << " total)"
             << endl;

        reinforcements--;
    }

    Territory *weakestTerritory = sortedTerritories[0];
    Territory *strongestTerritory = sortedTerritories[sortedTerritories.size() - 1];
    if ((strongestTerritory->getArmies() - weakestTerritory->getArmies()) >= 2) {
        auto *advanceOrder = new Advance(p, strongestTerritory, weakestTerritory, strongestTerritory->getArmies() - 1);
        p->getOrdersList()->addList(advanceOrder);
        cout << "\t+ Advance from " << strongestTerritory->getName() << " to " << weakestTerritory->getName() << endl;
    }

    if(p->getHand()->getCardNum() == 0) cout << p->getPlayerName() << " does not own any cards" << endl;
    else if (sortedTerritories.size() <= 3) cout << "All weakest territories have been defended. No card needed to be played." << endl;
    else {
        //removes all cards that are not for defending
        for(int i = 0; i < p->getHand()->getCardNum(); i++){
            if(p->getHand()->getCard(i).getType() != AIRLIFT)
                p->getHand()->removeCard(i);
        }
        //play the first card of the player's hand (an airlift card)
        //since the weakest territory would have already been defended by the strongest during advance,
        //take next weakest with next strongest
        Territory *nextWeakestTerritory = sortedTerritories[1];
        Territory *nextStrongestTerritory = sortedTerritories[sortedTerritories.size() - 2];
        if ((nextStrongestTerritory->getArmies() - nextWeakestTerritory->getArmies()) >= 2) {
            auto *cardOrder = new Airlift(p, nextStrongestTerritory, nextWeakestTerritory, nextStrongestTerritory->getArmies() - 1);
            p->getOrdersList()->addList(cardOrder);
            cout << "\t+ Airlift from " << nextStrongestTerritory->getName() << " to " << nextWeakestTerritory->getName() << endl;
        }

        //remove the played card
        p->getHand()->removeCard(0);

    }
}

string BenevolentPlayerStrategy::getType() {
    return "BENEVOLENT";
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player *player) {
    p = player;
}

vector<Territory *> NeutralPlayerStrategy::toAttack() {
    vector<Territory *> attacklist;
    return attacklist; //returns an empty list since cannot attack
}

vector<Territory *> NeutralPlayerStrategy::toDefend() {
    return p->getTerritoryList();
}

void NeutralPlayerStrategy::issueOrder() {
    for (Territory *t: p->getTerritoryList()) {
        cout << t->getName() << " - " << t->getArmies() << " troop(s)" << endl;
    }
    cout << "Neutral players do not issue orders or play cards" << endl;
}

string NeutralPlayerStrategy::getType() {
    return "NEUTRAL";
}

CheaterPlayerStrategy::CheaterPlayerStrategy(Player *player) {
    p = player;
}

vector<Territory *> CheaterPlayerStrategy::toAttack() {
    vector<Territory *> attackList;
    return attackList;
}

vector<Territory *> CheaterPlayerStrategy::toDefend() {
    vector<Territory *> defendList;
    return defendList;
}

void CheaterPlayerStrategy::cheat() {
    for (Territory *t: p->getTerritoryList()) {
        for (auto adjacent: *t->getAdjacentTerritories()) {
            //check if player owns the territory, if yes break
            if (adjacent->getPlayer()->getID() == p->getID()) {
                continue;
            } else {
                Player *enemy = adjacent->getPlayer();
                enemy->removeTerritory(adjacent);
                cout << "Cheater took " << adjacent->getName() << " from " << enemy->getPlayerName() << endl;
                adjacent->setPlayer(p);
                p->addTerritory(adjacent);
            }
        }
    }
}

void CheaterPlayerStrategy::issueOrder() {
    this->cheat();
    cout << "Cheater players do not issue orders or play cards" << endl;
}

string CheaterPlayerStrategy::getType() {
    return "CHEATER";
}