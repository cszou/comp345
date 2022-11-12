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
using namespace std;

class Player {

public:
    Player();//Default constructor
    Player(string name); //constructor with name
    Player(vector<Territory*> territories, Hand* hand, string name);//Constructor 3 params
    ~Player();//Desturctor
    Player(const Player&);//Copy constructor
    Player& operator =(const Player& p); //assigment operator
    void addOrder(Order* o);
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    void issueOrder();
    void printOrder();
    vector<Order*> getlist();
    Hand* gethandofcard();
    bool ownsTerritory(Territory* territory);//add
private:
    vector<Territory*> territories;
    Hand* handOfCards;
    vector<Order*> orderList;
    string name; 
    friend std::ostream & operator << (ostream &os, Player &p1);
};
