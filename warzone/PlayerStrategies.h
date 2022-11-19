#include <string>
#include"Player.h"
using namespace std;

class PlayerStrategy{
    private:
    Player* p;
    public:
    virtual void issueOrder()=0;
    virtual void toAttack()=0;
    virtual void toDedend()=0;  
};

class Neutral: public PlayerStrategy{

    public:
    Neutral();
    ~Neutral()
    void issueOrder()=0;
    void toAttack()=0;
    void toDedend()=0;  
};
class Cheater: public PlayerStrategy{

    public:
    Cheater();
    ~Cheater()
    void issueOrder()=0;
    void toAttack()=0;
    void toDedend()=0;  
};
class Human: public PlayerStrategy{

    public:
    Human();
    ~Human();
    void issueOrder()=0;
    void toAttack()=0;
    void toDedend()=0;  
};
class Aggressive: public PlayerStrategy{

    public:
    Aggressive();
    ~Aggressive();
    void issueOrder()=0;
    void toAttack()=0;
    void toDedend()=0;  
};
class Benevolent: public PlayerStrategy{

    public:
    void issueOrder()=0;
    void toAttack()=0;
    void toDedend()=0;  
};