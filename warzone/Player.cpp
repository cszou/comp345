#include "Player.h"
#include "Orders.h"
#include "Card.h"
#include "Map.h"
#include "PlayerStrategies.h"
#include <iostream>
using std::cin;
using std::cout;
#include <fstream>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

Player::Player()
{
	name = "noName";
	handOfCards = new Hand();
	orderList = new OrderList();
	reinforcement = 0;
	isEliminated = false; // for tournament mode only
}
// The const
Player::Player(string name)
{
	this->name = name;
	this->handOfCards = new Hand();
	orderList = new OrderList();
	reinforcement = 0;
	isEliminated = false; // for tournament mode only
}
Player::Player(string name, GameEngine *game)
{
	this->name = name;
	this->handOfCards = new Hand();
	orderList = new OrderList();
	reinforcement = 0;
	gameEngine = game;
	isEliminated = false; // for tournament mode only

} // constructor with name
GameEngine *Player::getGameEngine()
{
	return gameEngine;
}
string Player::getName()
{

	return this->name;
}
// Cons 4 params
Player::Player(vector<Territory *> territories, Hand *hand, string name, OrderList *orderList)
{
	for (auto t : territories)
	{
		this->territories.push_back(new Territory(*t));
	}
	this->handOfCards = new Hand(*hand);
	this->name = name;
	this->orderList = new OrderList(*orderList);
	isEliminated = false; // for tournament mode only

	std::cout << "created player" << endl;
}
// Destructor
Player::~Player()
{
	for (auto t : territories)
		delete t;
	delete handOfCards;
	delete orderList;
}
// Copy cons
Player::Player(const Player &p)
{
	this->name = p.name;
	for (auto t : p.territories)
		this->territories.push_back(new Territory(*t));
	this->handOfCards = new Hand(*p.handOfCards);
	this->orderList = new OrderList(*p.orderList);
			isEliminated = false; //for tournament mode only

}

Player &Player::operator=(const Player &p)
{
		isEliminated = false; //for tournament mode only
	this->name = p.name;
	for (auto t : p.territories)
		this->territories.push_back(new Territory(*t));
	this->handOfCards = new Hand(*p.handOfCards);
	this->orderList = new OrderList(*p.orderList);
	return *this;
}
bool Player::ownsTerritory(Territory *t1)
{
	for (Territory *t : territories)
	{
		if (t == t1)
		{
			return true;
		}
	}
	return false;
}
vector<Territory *> Player::getTerriotory()
{
	return territories;
}
void Player::addTerritory(Territory *o)
{
	territories.push_back(o);
	o->setOwner(this);
}

void Player::addOrder(Order *o)
{
	this->orderList->addOrders(o);
}
// Establish an arbitrary list of territories to be attacked
vector<Territory *> Player::toAttack()
{
	return ps->toAttack();
}
// Establish an arbitrary list of territories to be defended
vector<Territory *> Player::toDefend()
{
	return ps->toDedend();
}

Hand *Player::gethandofcard()
{
	return handOfCards;
}
// Link to Orders.cpp
OrderList *Player::getlist()
{
	return orderList;
}
// For testPlayers
void Player::printOrder()
{
	orderList->getorderlist();
	vector<Order *>::iterator it = orderList->getorderlist().begin();
	for (it; it < orderList->getorderlist().end(); it++)
	{
		std::cout << *it << std::endl;
	}
	cout << endl;
}

std::ostream &operator<<(ostream &os, Player &p1)
{
	return os << "Player: " << p1.name << " has " << p1.territories.size() << " territories and " << p1.handOfCards->numOfHandCards() << " cards.";
}

// Newly added methods
void Player::setTerritories(vector<Territory *> &t)
{

	this->territories = t;
}
void Player::setReinforcement(int reinforcement)
{
	this->reinforcement = reinforcement;
}

int Player::getReinforcement()
{
	return this->reinforcement;
}

bool Player::assignReinforcement(int num)
{
	if (num > this->reinforcement)
	{
		return false;
	}
	else
	{
		this->reinforcement -= num;
		return true;
	}
}

void Player::set_Deploy_Territories()
{
	for (int i = 0; i < territories.size(); i++)
	{
		Territory *t = territories[i];
		deploy_territories[t->getName()] = t;
	}
}
void Player::set_Available_Territories()
{
	vector<Territory *> enemy_territories = toAttack();
	//cout << "done" << endl;
	for (int i = 0; i < enemy_territories.size(); i++)
	{
		Territory *t = enemy_territories[i];
		available_territories[t->getName()] = t;
	}
}

void Player::clear_Deploy_Territories()
{

	deploy_territories.clear();
}
void Player::clear_Available_Territories()
{

	available_territories.clear();
}

void Player::set_all_territories(vector<Territory *> all)
{

	for (int i = 0; i < all.size(); i++)
	{
		Territory *t = all[i];
		all_territories[t->getName()] = t;
	}
}

void Player::set_players_Map(vector<Player *> players)
{
	for (int i = 0; i < players.size(); i++)
	{
		Player *p = players[i];
		players_Map[p->getName()] = p;
	}
}

void Player::issueOrder(string orderName)
{
	ps->issueOrder(orderName);
}

// Default constructor for creating a player base on the PlayerStrategy
Player::Player(PlayerStrategy *ps)
{
	this->ps = ps;
		isEliminated = false; //for tournament mode only

}
// Set player to change player strategy during excecution time
void Player::setPlayerStrategy(PlayerStrategy *newPlayerStrategy)
{
	this->ps = newPlayerStrategy;
}

std::map<string, Territory *> Player::getDeploy_territories()
{
	return deploy_territories;
}
std::map<string, Territory *> Player::getAvailable_territories()
{
	return available_territories;
}
std::map<string, Player *> Player::getPlayers_Map()
{
	return players_Map;
}

vector<Player *> Player::getAttackBan()
{
	return attackban;
}
void Player::setifattected()
{
	neverAttacked = true;
}
bool Player::getifattacked()
{
	return neverAttacked;
}
void Player::deleteTerriotory(Territory *o)
{
	territories.erase(find(territories.begin(), territories.end(), o));
}
void Player::eliminated()
{
	this->isEliminated = true;
}
bool Player::checkEliminated()
{
	return this->isEliminated;
}
void Player::reset()
{
	this->isEliminated = false;
	this->territories.clear();
}