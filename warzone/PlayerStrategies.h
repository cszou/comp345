#pragma once
#include <string>
#include"Player.h"
using namespace std;

class PlayerStrategy{
    protected:
    Player* p;
    public:
    PlayerStrategy(Player* player);
    virtual void issueOrder(string OrderName)=0;
    virtual vector<Territory*> toAttack()=0;
    virtual vector<Territory*> toDedend()=0;  
};

//Player that never issue any order, nor use any cards. If a Neutral player is attacked,
//it becomes an Aggressive player
class NeutralPlayerStrategy: public PlayerStrategy{
    private:
    string strategyName;
    public:
    NeutralPlayerStrategy(string strategy_Name,Player* player);
    ~NeutralPlayerStrategy();
    void issueOrder(string orderName);
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();  
    string getStrategyName();


};
class CheaterPlayerStrategy: public PlayerStrategy{

    public:
    CheaterPlayerStrategy();
    ~CheaterPlayerStrategy();
    void issueOrder(string orderName);
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();  
};
class HumanPlayerStrategy: public PlayerStrategy{

    public:
    HumanPlayerStrategy();
    ~HumanPlayerStrategy();
    void issueOrder(string orderName);
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();  
};
class AggressivePlayerStrategy: public PlayerStrategy{

    public:
    AggressivePlayerStrategy();
    ~AggressivePlayerStrategy();
    void issueOrder(string orderName);
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();  
};
class BenevolentPlayerStrategy: public PlayerStrategy{

    public:
    BenevolentPlayerStrategy();
    ~BenevolentPlayerStrategy();
    void issueOrder(string orderName);
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();   
};

    ~HumanPlayerStrategy();
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();  
};
class AggressivePlayerStrategy: public PlayerStrategy{

    public:
    AggressivePlayerStrategy();
    ~AggressivePlayerStrategy();
    void issueOrder(string orderName);
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();  
};
class BenevolentPlayerStrategy: public PlayerStrategy{

    public:
    BenevolentPlayerStrategy();
    ~BenevolentPlayerStrategy();
    void issueOrder(string orderName);
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();   
};
