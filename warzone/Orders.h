#pragma once
#include <iostream>
#include<vector>
#include<string>
//using namespace std;
#include "Card.h"
#include "LoggingObserver.h"
class Player;
class Territory;
class Deck;
class ILoggable;
class Subject;
class Order {
private:
public:
    Deck* d;
    Order();
    virtual bool validate();
    virtual ~Order();
    virtual void execute() = 0;
    friend std::ostream& operator<<(std::ostream& s, Order* i);//stream insertion operator


};
class Deploy : public Order {
private:
    bool* check;
    int* NUMBEROFARMY;
    Player* K;
    Territory* F;
    string name = "Deploy";
public:
    Deploy(int* NUMBEROFARMY, Player* K, Territory* F);
    ~Deploy();
    bool validate();
    void execute();
    friend std::ostream& operator<<(std::ostream& s, Deploy* i);//stream insertion operator

};

class Advance : public Order {
private:
    bool* check;
    int* NUMBEROFARMY;
    Player* K;
    Territory* OLD;
    Territory* NEW;
    string name = "Advance";
    static int numberoftime;
    //   Deck *d = new Deck();
public:
    Advance(Territory* old, Territory* new1, Player* player, int* NUMBEROFARMY);
    ~Advance();
    bool checkneibor(Territory* neww, Territory* oldd);
    bool validate();
    void execute();
    friend std::ostream& operator<<(std::ostream& s, Advance* i);//stream insertion operator

};
class Airlift : public Order {
private:
    int* NUMBEROFARMY;
    Player* K;
    Territory* OLD;
    Territory* NEW;
    string name = "Airlift";
public:
    Airlift(Player* K, Territory* OLD, Territory* NEW);
    ~Airlift();
    bool validate();
    void execute();
    friend std::ostream& operator<<(std::ostream& s, Airlift* i);//stream insertion operator

};

class Bomb : public Order {
private:
    bool* check;
    int* NUMBEROFARMY;
    Player* K;
    Territory* target;
    string name = "Bomb";
public:
    Bomb(Player* player, Territory* target, int* army);
    ~Bomb();
    bool validate();
    void execute();
    friend std::ostream& operator<<(std::ostream& s, Bomb* i);//stream insertion operator

};

class Blockade : public Order {
private:
    Player* K;
    Territory* target;
    string name = "Blockade";
public:
    Blockade(Player* k, Territory* target);
    ~Blockade();
    bool validate();
    void execute();
    friend std::ostream& operator<<(std::ostream& s, Blockade* i);//stream insertion operator

};



class Negotiate : public Order {
private:
    Player* order;
    Player* rival;
    string name = "Blockade";
public:
    Negotiate(Player* order, Player* rival);
    ~Negotiate();
    bool validate();
    void execute();
    friend std::ostream& operator<<(std::ostream& s, Negotiate* i);//stream insertion operator

};
class OrderList {
private:
    std::vector<Order*>list;//list of order of pointer
public:
    OrderList();
    OrderList(vector<Order*>list);
    void addOrders(Order* o);
    void setorderlist(vector<Order*>list);
    vector<Order*> getorderlist();
    ~OrderList();
    void removal(int i);
    int listsize();
    void move(int pos, int nextpos);
    void add(Order* k1);
    OrderList(const OrderList& orderlistobj);//copy constructor
    OrderList& operator = (const OrderList& d);//assignment operator
    friend std::ostream& operator<<(std::ostream& s, OrderList& ol);//stream insertion operator

};
