#include "Player.h"
#include "Orders.h"
#include "Card.h"
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
}
//Cons 4 params
Player::Player(string vector<Territory*> territories, vector<Continent*> continents, vector<Card*> deckOfCards, vector<Order*> list, name) 
{
	territories=territories;
    continents=continents;
    deckOfCards=deckOfCards;
    list=list; 
    name=name;
}
//Destructor
Player::~Player()
{
	territories.clear();
	continents.clear();
	deckOfCards.clear();
	list.clear();
    name.clear();
}
//Copy cons
Player::Player(const Player& p) 
{
	territories=p.territories;
    continents=p.continents;
    deckOfCards=p.deckOfCards;
    list=p.list; 
    name=p.name;
}
//Establish an arbitrary list of territories to be attacked
void Player::toAttack()
{
	for (int i = 0; i < territories.size(); i++) 
	{
		cout<<""<<*territories[i];
	}
}
//Establish an arbitrary list of territories to be defended
void Player::toDefend() 
{
	for (int i = 0; i < territories.size(); i++)
	{
		cout<<""<<*territories[i];
	}
}
//Create order object and puts it in the player’s list of orders
void Player::issueOrder(string order) 
{
	Order *o = new Order(list);
	list.push_back(o);
}
//Link to Orders.cpp
vector<Order*> Player::getlist() 
{
	return list;
}
//For testPlayers
void Player::printOrder() 
{
	vector<Order*>::iterator it = list.begin();
	for (; it != list.end(); it++)
	{
		cout<<""<<(*it)->getResult() ;
	}
	cout << endl;
}
