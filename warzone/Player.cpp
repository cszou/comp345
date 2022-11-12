#include "Player.h"
#include "Orders.h"
#include "Card.h"
#include "Map.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <fstream>
using std::ifstream;
using std::getline;
#include <string>
using std::string;
#include <vector>
using std::vector;
//#include <algorithm>
#include <sstream>
using std::stringstream;

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
Player::Player(vector<Territory*> territories, Hand* hand, string name, OrderList* orderList)
{
	for (auto t : territories)
		this->territories.push_back(new Territory(*t));
	this->handOfCards = new Hand(*hand);
	this->territories = territories;
	this->handOfCards = hand;
	this->name = name;
	this->orderList = new OrderList(*orderList);
}
//Destructor
Player::~Player()
{
	for (auto t : territories)
		delete t;
	delete handOfCards;
	delete orderList;
}
//Copy cons
Player::Player(const Player& p)
{
	this->name = p.name;
	for (auto t : p.territories)
		this->territories.push_back(new Territory(*t));
	this->handOfCards = new Hand(*p.handOfCards);
	this->orderList = new OrderList(*p.orderList);

}

Player& Player::operator=(const Player& p)
{
	this->name = p.name;
	for (auto t : p.territories)
		this->territories.push_back(new Territory(*t));
	this->handOfCards = new Hand(*p.handOfCards);
	this->orderList = new OrderList(*p.orderList);
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
	this->orderList->addOrders(o);
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
void Player::issueOrder(Order* o)
{
	std::cout<<"no method"<<std::endl;

}
Hand* Player::gethandofcard(){
	return handOfCards;
}
//Link to Orders.cpp
OrderList* Player::getlist()
{
	return orderList;
}
//For testPlayers
void Player::printOrder()
{
	orderList->getorderlist();
	vector<Order*>::iterator it =orderList->getorderlist().begin();
	for (it;it < orderList->getorderlist().end(); it++)
	{
		std::cout<<*it<<std::endl;
	}
	cout << endl;
}



std::ostream& operator<<(ostream& os, Player& p1)
{
	return os << "Player: " << p1.name <<" has " << p1.territories.size() << " territories and " << p1.handOfCards->numOfHandCards() << " cards.";
}
