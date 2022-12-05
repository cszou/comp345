#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include "Map.h"
#include "Card.h"
#include "Orders.h"

using namespace std;
class Command;
class Territory;
class Order;
class OrderList;
class Hand;
class PlayerStrategy;
class GameEngine;
class Player
{
public:
    Player(); // Default constructor
    Player(string name);
    Player(string name, GameEngine *game);                                                  // constructor with name                                                  // constructor with name
    Player(vector<Territory *> territories, Hand *hand, string name, OrderList *orderList); // Constructor 3 params
    ~Player();                                                                              // Desturctor
    Player(const Player &);                                                                 // Copy constructor
    Player &operator=(const Player &p);                                                     // assigment operator
    void addOrder(Order *o);
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
    void printOrder();
    void issueOrder(string orderName);
    OrderList *getlist();
    string getName();
    Hand *gethandofcard();
    bool ownsTerritory(Territory *territory); // add
    vector<Player *> attackban;
    vector<Territory *> getTerriotory();
    void addTerritory(Territory *o);

    // Newly added methods
    void setTerritories(vector<Territory *> &t);
    void setReinforcement(int reinforcement);
    int getReinforcement();
    bool assignReinforcement(int num);
    void set_Deploy_Territories();
    void set_Available_Territories();
    void clear_Deploy_Territories();
    void clear_Available_Territories();
    void set_all_territories(vector<Territory *> all);
    void set_players_Map(vector<Player *> players);

    // Newly added method for part 3
    void setIfAttected();
    void setPlayerStrategy(PlayerStrategy *newPlayerStrategy);
    Player(PlayerStrategy *ps);
    std::map<string, Territory *> getDeploy_territories();
    std::map<string, Territory *> getAvailable_territories();
    std::map<string, Player *> getPlayers_Map();
    vector<Player *> getAttackBan();
    void deleteTerriotory(Territory *o);
    void setifattected();
    bool getifattacked();
    GameEngine* getGameEngine();
    void eliminated();
    bool checkEliminated();
    void reset();
private:
    bool neverAttacked = false;
    vector<Territory *> territories;
    Hand *handOfCards;
    OrderList *orderList;
    string name;
    GameEngine *gameEngine;

    friend std::ostream &operator<<(ostream &os, Player &p1);

    // Newly added variables
    int reinforcement;
    std::map<string, Territory *> deploy_territories;
    std::map<string, Territory *> available_territories;
    std::map<string, Territory *> all_territories;
    vector<Player *> attackBan;
    std::map<string, Player *> players_Map;
    // Newly added for Player Strategy
    PlayerStrategy *ps;
        bool isEliminated;

};
