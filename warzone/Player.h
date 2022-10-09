#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
using namespace std;

class Player {

public:
    vector<Territory*> territories;
    vector<Continent*> continents;
    vector<Card*> deckOfCards;
    vector<Order*> list;
    Player();//Default constructor
    Player(string vector<Territory*> territories, vector<Continent*> continents, vector<Card*> deckOfCards, vector<Order*> list, name);//Constructor 5 params
    ~Player();//Desturctor
    Player(const Player&);//Copy constructor
    
    void toAttack();
    void toDefend();
    void issueOrder(string);
    void printOrder();
    vector<Order*> getlist();
private:
    string name; 
    ostream & operator << (ostream &os, Player &p1);
};
