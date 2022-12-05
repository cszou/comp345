#pragma once
#include <string>
#include "Player.h"
using namespace std;

class PlayerStrategy
{
protected:
    Player *p;

public:
    PlayerStrategy(Player *player);
    Player *getPlayer();
    virtual void issueOrder(string OrderName) = 0;
    virtual vector<Territory *> toAttack() = 0;
    virtual vector<Territory *> toDedend() = 0;
};

// Player that never issue any order, nor use any cards. If a Neutral player is attacked,
// it becomes an Aggressive player
class NeutralPlayerStrategy : public PlayerStrategy
{
private:
    string strategyName;

public:
    NeutralPlayerStrategy(Player *player);
    ~NeutralPlayerStrategy();
    void issueOrder(string orderName);
    vector<Territory *> toAttack();
    vector<Territory *> toDedend();
    string getStrategyName();
};
class CheaterPlayerStrategy : public PlayerStrategy
{
private:
    string strategyName;

public:
    CheaterPlayerStrategy(Player *player);
    ~CheaterPlayerStrategy();
    void issueOrder(string OrderName);
    vector<Territory *> toAttack();
    vector<Territory *> toDedend();
    string getStrategyName();
};
class HumanPlayerStrategy : public PlayerStrategy
{
private:
    string strategyName;

public:
    HumanPlayerStrategy(Player *player);
    ~HumanPlayerStrategy();
    void issueOrder(string OrderName);
    vector<Territory *> toAttack();
    vector<Territory *> toDedend();
    string getStrategyName();
};
class AggressivePlayerStrategy : public PlayerStrategy
{
private:
    string strategyName;

public:
    AggressivePlayerStrategy(Player *player);
    ~AggressivePlayerStrategy();
    void issueOrder(string OrderName);
    vector<Territory *> toAttack();
    vector<Territory *> toDedend();
    string getStrategyName();
};
class BenevolentPlayerStrategy : public PlayerStrategy
{
private:
    string strategyName;
public:
    BenevolentPlayerStrategy(Player *player);
    ~BenevolentPlayerStrategy();
    void issueOrder(string OrderName);
    vector<Territory *> toAttack();
    vector<Territory *> toDedend();
    string getStrategyName();
};