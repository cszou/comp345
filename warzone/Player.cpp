#include "Player.h"
#include "Orders.h"
#include "Card.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 
#include <sstream>
using namespace std;

//Default cons
Player::Player()
{
	handOfCards = new Hand();
}

Player::Player(string name) {
	this->name = name;
	this->handOfCards = new Hand();
}

//Cons 4 params
Player::Player(vector<Territory*> territories, Hand* hand, string name)
{
	this->territories = territories;
	this->handOfCards = hand;
	this->name = name;
}
//Destructor
Player::~Player()
{
	for (auto t : territories)
		delete t;
	delete handOfCards;
	for (auto o : orderList)
		delete o;
}
//Copy cons
Player::Player(const Player& p)
{
	this->name = p.name;
	for (auto t : p.territories)
		this->territories.push_back(new Territory(*t));
	this->handOfCards = new Hand(*p.handOfCards);
	for (auto o : p.orderList)
		this->orderList.push_back(new Order(*o));
}

Player& Player::operator=(const Player& p)
{
	this->name = p.name;
	for (auto t : p.territories)
		this->territories.push_back(new Territory(*t));
	this->handOfCards = new Hand(*p.handOfCards);
	for (auto o : p.orderList)
		this->orderList.push_back(new Order(*o));
	return *this;
}
bool Player::ownsTerritory(Territory* t1){
for(Territory* t:territories){
	if(t==t1){
		return true;
	}
}
return false;
}

void Player::addOrder(Order* o)
{
	this->orderList.push_back(o);
}
//Establish an arbitrary list of territories to be attacked
vector<Territory*> Player::toAttack()
{
	vector<Territory*> tAttack;
	tAttack.push_back(new Territory("QC"));
	tAttack.push_back(new Territory("ON"));
	return tAttack;
}
//Establish an arbitrary list of territories to be defended
vector<Territory*> Player::toDefend()
{
	vector<Territory*> tDefend;
	tDefend.push_back(new Territory("BC"));
	tDefend.push_back(new Territory("AB"));
	return tDefend;
}
//Create order object and puts it in the player’s list of orders
void Player::issueOrder()
{
	Advance *a = new Advance();
	orderList.push_back(a);
	Deploy* d = new Deploy();
	orderList.push_back(d);
	Bomb* b = new Bomb();
	orderList.push_back(b);
}
Hand* Player::gethandofcard(){
	return handOfCards;
}
//Link to Orders.cpp
vector<Order*> Player::getlist()
{
	return orderList;
}
//For testPlayers
void Player::printOrder()
{
	vector<Order*>::iterator it = orderList.begin();
	for (; it != orderList.end(); it++)
	{
		cout << "" << (*it);
	}
	cout << endl;
}



std::ostream& operator<<(ostream& os, Player& p1)
{
	return os << "Player: " << p1.name <<" has " << p1.territories.size() << " territories and " << p1.handOfCards->numOfHandCards() << " cards.";
}
