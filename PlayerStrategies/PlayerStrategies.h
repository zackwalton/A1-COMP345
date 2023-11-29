#ifndef PLAYERSTRATEGIES_H
#define PLAYERSTRATEGIES_H

#include<vector>
#include "Player.h"

using namespace std;

class Player;

class Territory;

class PlayerStrategy {
protected:
    Player *p;
public:
    virtual vector<Territory *> toAttack() = 0;

    virtual vector<Territory *> toDefend() = 0;

    virtual void issueOrder() = 0;

    virtual string getType() = 0;
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
    HumanPlayerStrategy(Player *player);

    vector<Territory *> toAttack();

    vector<Territory *> toDefend();

    void issueOrder();

    string getType();
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
    AggressivePlayerStrategy(Player *player);

    vector<Territory *> toAttack();

    vector<Territory *> toDefend();

    void issueOrder();

    string getType();
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
    BenevolentPlayerStrategy(Player *player);

    vector<Territory *> toAttack();

    vector<Territory *> toDefend();

    void issueOrder();

    string getType();
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
    NeutralPlayerStrategy(Player *player);

    vector<Territory *> toAttack();

    vector<Territory *> toDefend();

    void issueOrder();

    string getType();

};

class CheaterPlayerStrategy : public PlayerStrategy {
public:
    CheaterPlayerStrategy(Player *player);

    vector<Territory *> toAttack();

    vector<Territory *> toDefend();

    void issueOrder();

    string getType();
};

#endif
