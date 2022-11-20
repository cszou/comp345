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

class Neutral: public PlayerStrategy{

    public:
    Neutral();
    ~Neutral();
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();  
};
class Cheater: public PlayerStrategy{

    public:
    Cheater();
    ~Cheater();
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();  
};
class Human: public PlayerStrategy{

    public:
    Human();
    ~Human();
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();  
};
class Aggressive: public PlayerStrategy{

    public:
    Aggressive();
    ~Aggressive();
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();  
};
class Benevolent: public PlayerStrategy{

    public:
    Benevolent();
    ~Benevolent();
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDedend();   
};
