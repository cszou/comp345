#include <string>
#include"Player.h"
using namespace std;

class PlayerStrategy{
    private:
    Player* p;
    public:
    virtual void issueOrder()=0;
    virtual vector<Territory*> toAttack()=0;
    virtual vector<Territory*> toDedend()=0;  
};

class NeutralPlayerStrategy: public PlayerStrategy{

    public:
    NeutralPlayerStrategy();
    ~NeutralPlayerStrategy();
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();  
};
class CheaterPlayerStrategy: public PlayerStrategy{

    public:
    CheaterPlayerStrategy();
    ~CheaterPlayerStrategy();
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();  
};
class HumanPlayerStrategy: public PlayerStrategy{

    public:
    HumanPlayerStrategy();
    ~HumanPlayerStrategy();
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();  
};
class AggressivePlayerStrategy: public PlayerStrategy{

    public:
    AggressivePlayerStrategy();
    ~AggressivePlayerStrategy();
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();  
};
class BenevolentPlayerStrategy: public PlayerStrategy{

    public:
    BenevolentPlayerStrategy();
    ~BenevolentPlayerStrategy();
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();   
};
