#include <iostream>
#include <vector>
#include <string>
#include "Orders.h"

Order::Order()
{
    std::cout << "order created..." << std::endl;
}
Order::~Order()
{
} // destructor*/
//------------------------------------------------
Deploy::Deploy(int NUMBEROFARMY, Player *K, Territory *F)
{
    //    std::cout << F->getName() << std::endl;
    this->K = K;
    this->F = F;
    this->NUMBEROFARMY = NUMBEROFARMY;
    // std::cout<<this->F->getOwner()<<std::endl;
    std::cout << "initiate deploy!" << std::endl;
}
Deploy::~Deploy()
{
    std::cout << "deploy class destruction called" << std::endl;
    // add logobserver
}
bool Deploy::validate()
{
    //   std::cout << K << std::endl;
    //   std::cout << F->getOwner() << std::endl;
    if (K != F->getOwner())
    {
        cout << "false" << endl;
        return false;
    }
    else
    {
        cout << "true" << endl;
        return true;
    }
}
void Deploy::execute()
{
    if (validate())
    {
        std::cout << "Deploy amount: " << NUMBEROFARMY << std::endl;
        std::cout << "The terriotery is : " << F->getName() << std::endl;
        std::cout << "Previously has army: " << F->getNumberOfArmies() << std::endl;
        F->setNumberOfArmies(F->getNumberOfArmies() + NUMBEROFARMY);
        std::cout << "Now has army: " << F->getNumberOfArmies() << std::endl;
        check = true;
        std::cout << "Execute successful." << std::endl;
    }
    else
    {
        std::cout << "Execute unsuccessful since validated false." << std::endl;
    }
}
Deploy &Deploy::operator=(const Deploy &s)
{ // assignment operator
    if (this != &s)
    {
        this->F = new Territory(*(s.F));
        this->K = new Player(*(s.K));
        std::cout << "assignment operator initiated" << std::endl;
        this->NUMBEROFARMY = s.NUMBEROFARMY;
        return *this;
    }
    return *this;
}
std::ostream &operator<<(std::ostream &s, Deploy *deploy)
{
    return s << "This is a deploy order" << std::endl; // string insertion operator
}
string Deploy::getName()
{
    return name;
}
string Deploy::stringToLog()
{
    return "Order Executed: " + name;
}
//-------------------------------ADVANCE-------------------------------------------------------
Advance::Advance(Territory *old, Territory *new1, Player *player, int NUMBEROFARMY)
{
    this->OLD = old;
    this->NEW = new1;
    this->NUMBEROFARMY = NUMBEROFARMY;
    this->K = player;
    d = new Deck();
    std::cout << "initiate advance!" << std::endl;
}
Advance::~Advance()
{
    std::cout << "advance class destruction called" << std::endl;
    // detach()
}

bool Advance::validate()
{
    for (Territory *i : OLD->getNeighbours())
    {
        std::cout << "advance class destruction called" << std::endl;
        if (&NEW == &i) // if new is not neibor of old
            return false;
    }
    if (OLD->getOwner() != K)
    {
        std::cout << "advance class destruction called" << std::endl;
        return false;
    }
    else
    {
        std::cout << "advance verified successful" << std::endl;
        return true;
    }
}
void Advance::execute()
{
    if (validate())
    {
        if (OLD->getOwner() == NEW->getOwner())
        {
            std::cout << "ARMY FROM OLD PLACE:" << OLD->getNumberOfArmies() << std::endl;
            std::cout << "ARMY FROM NEW PLACE:" << NEW->getNumberOfArmies() << std::endl;
            NEW->setNumberOfArmies(NEW->getNumberOfArmies() + OLD->getNumberOfArmies());
            std::cout << "UPDATE! ARMY FROM NEW PLACE:" << NEW->getNumberOfArmies() << std::endl;
        }    // SAME OWNER BETWEEN TEROIRO
        else /*OLD->getOwner()!=NEW->getOwner()*/
        {    // attack
            std::cout << "Teroery has different owner!!!" << std::endl;
            if (OLD->getNumberOfArmies() * 0.6 >= NEW->getNumberOfArmies())
            {
                std::cout << "get" << std::endl;
                NEW->setNumberOfArmies(OLD->getNumberOfArmies() - 0.7 * NEW->getNumberOfArmies());
                OLD->setNumberOfArmies(0);
                NEW->setOwner(OLD->getOwner()); // owner changed!
                OLD->getOwner()->addTerriotory(NEW);
                if (numberoftime == 0)
                {
                    std::cout << "Currently holding cards: " << OLD->getOwner()->gethandofcard()->numOfHandCards() << std::endl;
                    OLD->getOwner()->gethandofcard()->add_CardinHand(d->draw()); // add card in hand
                    std::cout << "One new card draw from deck,advance successfully" << std::endl;
                    std::cout << "Currently holding cards: " << OLD->getOwner()->gethandofcard()->numOfHandCards() << endl;
                }
                else
                    std::cout << "no new card will give,since more than one advance sofar!" << std::endl;
            }
            else if (NEW->getNumberOfArmies() * 0.7 < OLD->getNumberOfArmies() && OLD->getNumberOfArmies() * 0.6 < NEW->getNumberOfArmies())
            {
                // old 150 new 200
                int nold = OLD->getNumberOfArmies();
                int nnew = NEW->getNumberOfArmies();
                OLD->setNumberOfArmies(nold - nnew * 0.7);
                NEW->setNumberOfArmies(nnew - nold * 0.6);
                std::cout << "half half both got damaged" << std::endl;
            }
            else if (NEW->getNumberOfArmies() * 0.7 >= OLD->getNumberOfArmies())
            {
                // new 20 old 130
                NEW->setNumberOfArmies(NEW->getNumberOfArmies() - OLD->getNumberOfArmies() * 0.6);
                OLD->setNumberOfArmies(0);
                std::cout << "target cant make,own tero become 0" << std::endl;
            }
            else
                std::cout << "dont know whats the condition" << std::endl;
        }
        std::cout << "advance order validated!" << std::endl;
    }

    //   Advance::Advance(const Advance& s){
}
std::ostream &operator<<(std::ostream &s, Advance *i)
{
    return s << "Advance order meaning: To move forward" << std::endl; // string insertion operator
}
Advance::Advance(const Advance &advance)
{
    this->OLD = advance.OLD;
    this->NEW = advance.NEW;
    this->NUMBEROFARMY = advance.NUMBEROFARMY;
    this->K = advance.K;
    this->d = advance.d;
    std::cout << "initiate copy consturctor!" << std::endl;
}
Advance &Advance::operator=(const Advance &add)
{
    // Intentionally shallow copying data members of deploy class since no new members are being created
    if (&add != this)
    {
        this->OLD = add.OLD;
        this->NEW = add.NEW;
        this->NUMBEROFARMY = add.NUMBEROFARMY;
        this->K = add.K;
        this->d = add.d;
        std::cout << "initiate assignment operator consturctor!" << std::endl;
    }
    std::cout << "initiate assignment operator consturctor!" << std::endl;
    return *this;
}
string Advance::getName()
{
    return name;
}
string Advance::stringToLog()
{
    return "Order Executed: " + name;
}

//-----------------------------------Airlift-----------------------
Airlift::Airlift(Player *K, Territory *OLD, Territory *NEW)
{
    this->OLD = OLD;
    this->NEW = NEW;
    this->K = K;
    std::cout << "initiate airlift!" << std::endl;
}
Airlift::~Airlift()
{
    std::cout << "airlift class destruction called" << std::endl;
}
Airlift::Airlift(const Airlift &kk)
{
    this->OLD = kk.OLD;
    this->NEW = kk.NEW;
    this->K = kk.K;
    std::cout << "initiate copy consturctor!" << std::endl;
}

bool Airlift::validate()
{
    if (OLD->getOwner() != NEW->getOwner())
    {
        std::cout << "unseccess varificatoin,since owner of two tero not the same!" << std::endl;
        return false;
    }
    else
    {
        return true;
        std::cout << "airlift order validated!" << std::endl;
    }
}
void Airlift::execute()
{
    if (validate())
    {
        std::cout << "source terriotery,currently: " << OLD->getNumberOfArmies() << std::endl;
        std::cout << "target terriotery,currently: " << NEW->getNumberOfArmies() << std::endl;
        int number;
        std::cout << "choose the amount of army from source terriotery,currently: " << OLD->getNumberOfArmies() << std::endl;
        std::cin >> number;
        if (0 <= number && number <= OLD->getNumberOfArmies())
        {
            NEW->setNumberOfArmies(NEW->getNumberOfArmies() + number);
            std::cout << "UPDATE! target terriotery : " << NEW->getNumberOfArmies() << std::endl;
            OLD->setNumberOfArmies(OLD->getNumberOfArmies() - number);
        }
        else
            std::cout << "cannot execute since validation failded" << std::endl;
    }
    std::cout << "airlift order executed!" << std::endl;
}
std::ostream &operator<<(std::ostream &s, Airlift *i)
{
    return s << "Airlift order meaning: To move supply or army by air to a specific area" << std::endl; // string insertion operator
}
string Airlift::getName()
{
    return name;
}
string Airlift::stringToLog()
{
    return "Order Executed: " + name;
}
//-----------------------------------BOMB---------------------------
Bomb::Bomb(Player *player, Territory *target, int *army)
{
    this->NUMBEROFARMY = army;
    this->target = target;
    this->K = player;

    std::cout << "initiate bomb!" << std::endl;
}
Bomb::~Bomb()
{
    std::cout << "bomb class destruction called" << std::endl;
}
bool Bomb::validate()
{
    if (target->getOwner() == K)
        return false;
    bool verif = false;
    for (auto it : target->getNeighbours())
    {
        if (K->ownsTerritory(it))
        {
            verif = true;
            return true;
        }
    }
    return false;
}
void Bomb::execute()
{
    if (validate())
    {
        int record = target->getNumberOfArmies();
        target->setNumberOfArmies(target->getNumberOfArmies() / 2);
        std::cout << "bomb order executed!Previous target army: " << record << ",Currently target terriotery army: " << target->getNumberOfArmies() << std::endl;
    }
    else
        std::cout << "verification failed" << std::endl;
    std::cout << "bomb execute method finished !" << std::endl;
}

std::ostream &operator<<(std::ostream &s, Bomb *i)
{
    return s << "Bomb order meaning: To air raid specific area" << std::endl; // string insertion operator
}

//---------------------------------------Blockade-----------------
Blockade::Blockade(Player *k, Territory *target)
{
    this->K = k;
    this->target = target;
    std::cout << "initiate blockade!" << std::endl;
}
Blockade::~Blockade()
{
    std::cout << "blockade class destruction called" << std::endl;
}
bool Blockade::validate()
{
    if (!K->ownsTerritory(target))
    {
        std::cout << "blockade order validated!" << std::endl;
        return false;
    }
    else
    {
        std::cout << "blockade order validated!" << std::endl;
        return true;
    }
}
void Blockade::execute()
{
    if (validate())
    {
        target->setNumberOfArmies(target->getNumberOfArmies() * 2); // double the army amount
        target->setOwner(nullptr);                                  // set owner to null
        std::cout << "blockade order executed!" << std::endl;
    }
    std::cout << "blockade order failed!" << std::endl;
}

std::ostream &operator<<(std::ostream &s, Blockade *i)
{
    return s << "Blockade order meaning: To block a specific area" << std::endl; // string insertion operator
}

// negotiator----------------------------------------------------------
Negotiate::Negotiate(Player *order, Player *rival)
{
    this->order = order;
    this->rival = rival;
    std::cout << "initiate negotiate!" << std::endl;
}
Negotiate::~Negotiate()
{
    std::cout << "negotiate class destruction called" << std::endl;
}
bool Negotiate::validate()
{
            std::cout << "negotiate order validate!" << std::endl;

    if (order == rival)
    {
        std::cout << "negotiate order unsuccessfully validated!" << std::endl;
        return false;
    }
    else
    {
        std::cout << "negotiate order successfully validated!" << std::endl;
        return true;
    }
    // validate part
    std::cout << "negotiate order validated!" << std::endl;
}
void Negotiate::execute()
{
    if (validate())
    {
        order->attackban.push_back(rival);
        rival->attackban.push_back(order);
        std::cout << "negotiate order executed!" << std::endl;
    }else
    std::cout << "negotiate order failed!" << std::endl;
}
std::ostream &operator<<(std::ostream &s, Negotiate *i)
{
    return s << "Negotiate order meaning: To negociate with the rebel or other players" << std::endl; // string insertion operator
}

//---------------------------------------ORDERLIST-------------------------------------
OrderList::OrderList()
{
    std::cout << "default orderlist" << std::endl;
}
OrderList::OrderList(vector<Order *> list)
{
    this->list = list;
}
OrderList::~OrderList()
{
    std::cout << "Destroying OrdersList" << std::endl;
    for (auto order1 : list)
    {
        delete order1;
        order1 = NULL;
    }
    std::cout << "pointers destroyed" << std::endl;
    list.clear();
    std::cout << "orderlist destroyed" << std::endl;
}
void OrderList::setorderlist(vector<Order *> list)
{
    this->list = list;
}
//------------------------------
void OrderList::addOrders(Order *o)
{
    this->list.push_back(o);
}
vector<Order *> OrderList::getorderlist()
{
    return list;
}

void OrderList::add(Order *k1)
{
    list.push_back(k1);
}
std::ostream &operator<<(std::ostream &s, OrderList &ol) // string insertion operator for orderlists
{
    return s << "This is a list of orders." << std::endl;
}
