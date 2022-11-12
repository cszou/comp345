#pragma once

#include <iostream>
#include<vector>
#include<string>
//using namespace std;
class Player;
class Territory;
class Desk;
class Order {
    private:
 /* std::string name;
    std::string nameofterio;
    Player* players; 
    Territory* land;*/
    Deck *d ;
    friend class Advance;
    public:
    Order();
    virtual bool validate();
    virtual ~Order();
    virtual std::string call();
    std::string description();
    virtual void execute()=0;
    void nameaccess(std::string newname);
    Order(const Order& e);//copy constructor
    Order& operator=(const Order& e);//assignment operator
    friend std::ostream& operator<<(std::ostream &s,  Order *i) ;//stream insertion operator
};
class Deploy : public Order{
    private:
    bool* check;
    int *NUMBEROFARMY;
    Player *K;
    Territory *F;
    public:
    Deploy(int* NUMBEROFARMY,Player *K,Territory *F);
    ~Deploy();
    bool validate();
    void execute();
    Deploy(const Deploy& s);//copy constructor
    Deploy& operator=(const Deploy& s);//assignment operator
    friend std::ostream& operator<<(std::ostream &s,  Deploy *i) ;//stream insertion operator
};
     
class Advance : public Order{
    private:
    bool* check;
    int *NUMBEROFARMY;
    Player *K;
    Territory *OLD;
    Territory *NEW;
    static int numberoftime;
 //   Deck *d = new Deck();
    public:    
    Advance(Territory *old,Territory *new1,Player *player,int* NUMBEROFARMY);
    ~Advance();
    bool checkneibor(Territory* neww,Territory* oldd);
    bool validate();
    void execute();
    Advance(const Advance& s);//copy constructor
    Advance& operator=(const Advance& s);//assignment operator
    friend std::ostream& operator<<(std::ostream &s,  Advance *i) ;//stream insertion operator
};
class Airlift : public Order{
    private:
    int *NUMBEROFARMY;
    Player *K;
    Territory *OLD;
    Territory *NEW;
    public:
    Airlift::Airlift(Player *K,Territory *OLD,Territory *NEW);
    ~Airlift();
    bool validate();
    void execute();
    Airlift(const Airlift& s);//copy constructor
    Airlift& operator=(const Airlift& s);//assignment operator
    friend std::ostream& operator<<(std::ostream &s,  Airlift *i) ;//stream insertion operator

};

class Bomb : public Order{
    private:
    bool* check;
    int *NUMBEROFARMY;
    Player *K;
    Territory *target;
    public:
    Bomb(Player* player,Territory* target,int* army );
    ~Bomb();
    bool validate();
    void execute();
    Bomb(const Bomb& s);//copy constructor
    Bomb& operator=(const Bomb& s);//assignment operator
    friend std::ostream& operator<<(std::ostream &s,  Bomb *i) ;//stream insertion operator
};

class Blockade : public Order{
    private:
    Player *K;
    Territory *target;
    public:
    Blockade(Player* k,Territory* target);
    ~Blockade();
    bool validate();
    void execute();
    Blockade(const Blockade& s);//copy constructor
    Blockade& operator=(const Blockade& s);//assignment operator
    friend std::ostream& operator<<(std::ostream &s,  Blockade *i) ;//stream insertion operator
};



class Negotiate : public Order{
    private:
    Player *order;
    Player *rival;
    public:
    Negotiate(Player *order,Player* rival);
    ~Negotiate();
    bool validate();
    void execute();
    Negotiate(const Negotiate& s);//copy constructor
    Negotiate& operator=(const Negotiate& s);//assignment operator
    friend std::ostream& operator<<(std::ostream &s,  Negotiate *i) ;//stream insertion operator

};
class OrderList{
    public:
    OrderList(vector<Order*>list);
    void addOrders(Order* o);
    std::vector<Order*>list;//list of order of pointer
    void setorderlist(vector<Order*>list);
    vector<Order*> getorderlist();
    ~OrderList();
    void removal(int i);
    int listsize();
    void move(int pos,int nextpos);
    void add(Order* k1);
    OrderList(const OrderList& orderlistobj);//copy constructor
    OrderList &  operator = (const OrderList& d);//assignment operator
    friend std::ostream& operator<<(std::ostream& s, OrderList& ol);//stream insertion operator
};
