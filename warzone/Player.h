#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Map.h"
#include "Card.h"
#include "Orders.h"
//using namespace std;
class Territory;
class Hand; 
class OrderList;
class Order;

class Player {

public:
    Player();//Default constructor
    Player(string name); //constructor with name
    Player(vector<Territory*> territories, Hand* hand, string name, OrderList* orderList);//Constructor 3 params
    ~Player();//Desturctor
    Player(const Player&);//Copy constructor
    Player& operator =(const Player& p); //assigment operator
    void addOrder(Order* o);
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    void issueOrder(Order* o);
    void printOrder();
    OrderList* getlist();
    Hand* gethandofcard();
    bool ownsTerritory(Territory* territory);//add
    vector<Player*> attackban; 
private:
    vector<Territory*> territories;
    Hand* handOfCards;
    OrderList* orderList;
    string name; 
    friend std::ostream & operator << (std::ostream &os, Player &p1);
};
