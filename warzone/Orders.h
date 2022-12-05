#pragma once
#include <iostream>
#include<vector>
#include<string>
//using namespace std;
#include "Card.h"
#include "LoggingObserver.h"
#include "Player.h"
#include "Map.h"
#include "GameEngine.h"

class Player;
class Territory;
class Deck;
class ILoggable;
class Subject;
class GameEngine;

class Order : public ILoggable, public Subject {
    protected:
    GameEngine* game;
    public:
    Deck *d ;
    Order();
    virtual bool validate()=0;
    virtual ~Order();
    virtual void execute()=0;
    virtual string getName()=0;
    
  
};
class Deploy : public Order{
    private:
    bool check;
    int NUMBEROFARMY;
    Player *K;
    Territory *F;
    string name = "Deploy";
    public:
    Deploy(int NUMBEROFARMY,Player *K,Territory *F);
    ~Deploy();
    bool validate();
    void execute();
    friend std::ostream& operator<<(std::ostream &s,  Deploy *i) ;//stream insertion operator
    string stringToLog();
    string getName();
    Deploy& operator=(const Deploy& s); //assignment operator
};
     
class Advance : public Order{
    private:
    bool* check;
    int NUMBEROFARMY;
    Player *K;
    Territory *OLD;
    Territory *NEW;
    string name = "Advance";
     int numberoftime=0;
 //   Deck *d = new Deck();
    public:
    Advance(const Advance &advance);
    Advance(Territory *old,Territory *new1,Player *player,int NUMBEROFARMY);
    ~Advance();
    bool checkneibor(Territory* neww,Territory* oldd);
    bool validate();
    void execute();
    friend std::ostream& operator<<(std::ostream &s,  Advance *i) ;//stream insertion operator
    string stringToLog();
    string getName();
    Advance& operator = (const Advance& add);

};
class Airlift : public Order{
    private:
    int *NUMBEROFARMY;
    Player *K;
    Territory *OLD;
    Territory *NEW;
    string name = "Airlift";
    public:
    Airlift(Player *K,Territory *OLD,Territory *NEW);
    Airlift(const Airlift &kk);
    ~Airlift();
    bool validate();
    void execute();
    friend std::ostream& operator<<(std::ostream &s,  Airlift *i) ;//stream insertion operator
    string stringToLog();
    string getName();
};

class Bomb : public Order{
    private:
    bool* check;
    int *NUMBEROFARMY;
    Player *K;
    Territory *target;
    string name = "Bomb";
    public:
    Bomb(Player* player,Territory* target,int* army );
    ~Bomb();
    bool validate();
    void execute();
    friend std::ostream& operator<<(std::ostream &s,  Bomb *i) ;//stream insertion operator
    string stringToLog();
    string getName();
};

class Blockade : public Order{
    private:
    Player *K;
    Territory *target;
    string name = "Blockade";
    public:
    Blockade(Player* k,Territory* target);
    ~Blockade();
    bool validate();
    void execute();
    friend std::ostream& operator<<(std::ostream &s,  Blockade *i) ;//stream insertion operator
    string stringToLog();
    string getName();
};



class Negotiate : public Order{
    private:
    Player *order;
    Player *rival;
    string name = "Blockade";
    public:
    Negotiate(Player *order,Player* rival);
    ~Negotiate();
    bool validate();
    void execute();
    friend std::ostream& operator<<(std::ostream &s,  Negotiate *i) ;//stream insertion operator
    string stringToLog();
    string getName();
};
class OrderList : public ILoggable, public Subject{
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
    void add(Order* k1);
    string stringToLog();
    friend std::ostream& operator<<(std::ostream& s, OrderList& ol);//stream insertion operator

};
