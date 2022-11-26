#include "Player.h"
#include "Orders.h"
#include "Card.h"
#include "Map.h"
#include"PlayerStrategies.h"
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
using namespace std;

// Default constructor for creating a player base on the PlayerStrategy
Player::Player(PlayerStrategy* ps){
	this->ps = ps;
}
// Set player to change player strategy during excecution time
void Player::setPlayer(PlayerStrategy* newPlayerStrategy){
	this->ps = newPlayerStrategy;
}
Player::Player()
{
	name = "noName";
	handOfCards = new Hand();
	orderList = new OrderList();
	reinforcement = 0;
}
//The const
Player::Player(string name)
{
	this->name = name;
	this->handOfCards = new Hand();
	orderList = new OrderList();
	reinforcement = 0;
}
string Player::getName()
{
	return this->name;
}
// Cons 4 params
Player::Player(vector<Territory*> territories, Hand* hand, string name, OrderList* orderList)
{
	for (auto t : territories)
	{
		this->territories.push_back(new Territory(*t));
	}
	this->handOfCards = new Hand(*hand);
	this->name = name;
	this->orderList = new OrderList(*orderList);
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
bool Player::ownsTerritory(Territory* t1)
{
	for (Territory* t : territories)
	{
		if (t == t1)
		{
			return true;
		}
	}
	return false;
}
vector<Territory*> Player::getTerriotory()
{
	return territories;
}
void Player::addTerritory(Territory* o)
{
	territories.push_back(o);
}

void Player::addOrder(Order* o)
{
	this->orderList->addOrders(o);
}
// Establish an arbitrary list of territories to be attacked
vector<Territory*> Player::toAttack()
{
	vector<Territory*> bannedTerritory;
	for (int i = 0; i < attackBan.size(); i++) {
		vector<Territory*> player_territories = attackBan[i]->getTerriotory();
		for (int k = 0; k < player_territories.size(); k++) {
			Territory* t = player_territories[k];
			if (find(bannedTerritory.begin(), bannedTerritory.end(), t) == bannedTerritory.end()) {
				bannedTerritory.push_back(t);
			}
		}
	}
	vector<Territory*> tAttack;
	for (int i = 0; i < territories.size(); i++) {
		vector<Territory*> neignbours = territories[i]->getNeighbours();
		for (int k = 0; k < neignbours.size(); k++) {
			if ((find(tAttack.begin(), tAttack.end(), neignbours[k]) == tAttack.end())
				&& find(bannedTerritory.begin(), bannedTerritory.end(), neignbours[k]) == bannedTerritory.end())
			{
				tAttack.push_back(neignbours[k]);
			}
		}
	}
	for (int i = 0; i < territories.size(); i++) {
		if (find(tAttack.begin(), tAttack.end(), territories[i]) == tAttack.end()) {
			tAttack.push_back(territories[i]);
		}
	}
	return tAttack;
}
// Establish an arbitrary list of territories to be defended
vector<Territory*> Player::toDefend()
{
	return this->territories;
}

Hand* Player::gethandofcard()
{
	return handOfCards;
}
// Link to Orders.cpp
OrderList* Player::getlist()
{
	return orderList;
}
// For testPlayers
void Player::printOrder()
{
	orderList->getorderlist();
	vector<Order*>::iterator it = orderList->getorderlist().begin();
	for (it; it < orderList->getorderlist().end(); it++)
	{
		std::cout << *it << std::endl;
	}
	cout << endl;
}

std::ostream& operator<<(ostream& os, Player& p1)
{
	return os << "Player: " << p1.name << " has " << p1.territories.size() << " territories and " << p1.handOfCards->numOfHandCards() << " cards.";
}

//Newly added methods
void Player::setTerritories(vector<Territory*>& t) {

	this->territories = t;

}
void Player::setReinforcement(int reinforcement) {
	this->reinforcement = reinforcement;
}

int Player::getReinforcement() {
	return this->reinforcement;
}

bool Player::assignReinforcement(int num) {
	if (num > this->reinforcement) {
		return false;
	}
	else {
		this->reinforcement -= num;
		return true;
	}

}

void Player::set_Deploy_Territories() {

	for (int i = 0; i < territories.size(); i++) {
		Territory* t = territories[i];
		deploy_territories[t->getName()] = t;

	}

}

void Player::set_Available_Territories() {

	vector<Territory*> enemy_territories = toAttack();
	cout << "done" << endl;
	for (int i = 0; i < enemy_territories.size(); i++) {
		Territory* t = enemy_territories[i];
		available_territories[t->getName()] = t;

	}

}

void Player::clear_Deploy_Territories() {

	deploy_territories.clear();

}
void Player::clear_Available_Territories() {

	available_territories.clear();


}

void Player::set_all_territories(vector<Territory*> all) {

	for (int i = 0; i < all.size(); i++) {
		Territory* t = all[i];
		all_territories[t->getName()] = t;

	}


}

void Player::set_players_Map(vector<Player*> players) {
	for (int i = 0; i < players.size(); i++) {
		Player* p = players[i];
		players_Map[p->getName()] = p;
	}

}

bool Player::issueOrder(string s)
{
	set_Deploy_Territories();
	set_Available_Territories();
	cout << "Order Issuing phase for player " << this->name << endl;
	bool finished = false;
	//Case deploy
	if (s == "Deploy") {
		cout << "Please enter a deployement order" << endl;
		cout << "Your territories are: ";
		for (auto t : this->getTerriotory())
			cout << t->getName() << "  ";
		cout << endl;
		cout << "You have " << this->reinforcement << " troops left in your reinforcement tool, please enter the number of troops you want to use" << endl;
		int num;
		cin >> num;
		while (!cin) {
			cout << "Wrong data type. Please try again. " << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> num;
		}
		if (num > reinforcement) {
			num = reinforcement;
		}
		cout << "Where do you want to deploy " << num << " troops? Please enter the name of the territory. " << endl;
		string name;
		cin >> name;
		while (deploy_territories.find(name) == deploy_territories.end()) {
			cout << "Wrong name, please try again." << endl;
			cin >> name;
		}
		cout << "Order type: Deploy " << num << " -> " << name << endl;
		reinforcement -= num;
		addOrder(new Deploy(num, this, deploy_territories[name]));

		//Execute order
		Order* o = orderList->getorderlist().back();
		
	        o->execute();
		
		orderList->getorderlist().pop_back();



		cout << "Are you done issuing orders? (Yes/No)" << endl;
		string s;
		cin >> s;
		if (s == "Yes" && reinforcement == 0) {
			finished = true;

		}
		return finished;

	}
	else {
		//Other case
		vector<string> Order_names;
		Order_names.push_back("Advance");
		vector<Card*> cards = handOfCards->get_VectorOfHand();
		for (int i = 0; i < cards.size(); i++) {
			Order_names.push_back(cards[i]->get_cardType());
		}
		cout << "Please choose one of the options: " << endl;
		cout << "-- Advance" << endl;
		if (Order_names.size() > 1) {
			cout << "Use one of the cards: " << endl;
			for (int k = 1; k < Order_names.size(); k++) {
				cout << "-- " << Order_names[k] << endl;
			}
		}
		string input;
		cin >> input;
		while (find(Order_names.begin(), Order_names.end(), input) == Order_names.end()) {
			cout << "No such option, try again" << endl;
			cin >> input;
		}
		//Advance
		if (input == "Advance") {
			cout << "Your territories are: ";
			for (std::map<string, Territory*>::iterator it = deploy_territories.begin(); it != deploy_territories.end(); ++it) {

				cout << it->first << "  ";

			}
			cout << endl;
			cout << "Choose the source territory: ";
			string source_name;
			cin >> source_name;
			while (deploy_territories.find(source_name) == deploy_territories.end()) {
				cout << "Wrong name, please try again." << endl;
				cin >> source_name;
			}
			int army_num = deploy_territories[source_name]->getNumberOfArmies();
			cout << "You have " << army_num << " army unites in this territory, how many do you want to move? " << endl;

			int num;
			cin >> num;
			while (!cin) {
				cout << "Wrong data type. Please try again. " << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> num;
			}
			if (num > army_num) {
				num = army_num;
			}
			cout << "Please enter the target territory: " << endl;
			cout << "The available options are your territories and the enemy territories" << endl;
			cout << "Available territories are: ";
			for (std::map<string, Territory*>::iterator it = available_territories.begin(); it != available_territories.end(); ++it) {

				cout << it->first << "  ";

			}
			cout << endl;
			string target_name;
			cin >> target_name;
			while (available_territories.find(target_name) == available_territories.end()) {
				cout << "Wrong name, please try again." << endl;
				cin >> target_name;
			}
			addOrder(new Advance(available_territories[source_name], available_territories[target_name], this, num));


		}

		//Bomb card
		else if (input == "bomb") {
			cout << "Using the bomb card, please choose a territory" << endl;
			cout << "Available territories are: ";
			for (std::map<string, Territory*>::iterator it = available_territories.begin(); it != available_territories.end(); ++it) {

				cout << it->first << "  ";

			}
			string target_name;
			cin >> target_name;
			while (available_territories.find(target_name) == available_territories.end()) {
				cout << "Wrong name, please try again." << endl;
				cin >> target_name;
			}
			addOrder(new Bomb(this, available_territories[target_name], 0));
			handOfCards->remove_CardinHand_ByType("bomb");
		}



		if (input == "blockade") {
			cout << "Using the bomb card, please choose one of your territory" << endl;
			cout << "Available territories are: ";
			for (std::map<string, Territory*>::iterator it = deploy_territories.begin(); it != deploy_territories.end(); ++it) {

				cout << it->first << "  ";

			}
			string target_name;
			cin >> target_name;
			while (deploy_territories.find(target_name) == deploy_territories.end()) {
				cout << "Wrong name, please try again." << endl;
				cin >> target_name;
			}
			addOrder(new Blockade(this, available_territories[target_name]));
			handOfCards->remove_CardinHand_ByType("blockade");
		}

		//Air Lift
		else if (input == "airlift") {
			cout << "Using this airlift card" << endl;
			cout << "Your territories are: ";
			for (std::map<string, Territory*>::iterator it = deploy_territories.begin(); it != deploy_territories.end(); ++it) {

				cout << it->first << "  ";

			}
			cout << "Choose the source territory";
			string source_name;
			cin >> source_name;
			while (deploy_territories.find(source_name) == deploy_territories.end()) {
				cout << "Wrong name, please try again." << endl;
				cin >> source_name;
			}
			int army_num = deploy_territories[source_name]->getNumberOfArmies();
			cout << "You have " << army_num << "army unites in this territory, how many do you want to move ?" << endl;

			int num;
			cin >> num;
			while (!cin) {
				cout << "Wrong data type. Please try again. " << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> num;
			}
			if (num > army_num) {
				num = army_num;
			}
			cout << "Please enter the target territory" << endl;
			cout << "The available options are your territories and the enemy territories" << endl;
			cout << "Available territories are: ";
			for (std::map<string, Territory*>::iterator it = deploy_territories.begin(); it != deploy_territories.end(); ++it) {

				cout << it->first << "  ";

			}
			string target_name;
			cin >> target_name;
			while (deploy_territories.find(target_name) == deploy_territories.end()) {
				cout << "Wrong name, please try again." << endl;
				cin >> target_name;
			}
			addOrder(new Airlift(this, deploy_territories[source_name], deploy_territories[target_name]));
			handOfCards->remove_CardinHand_ByType("airlift");
		}
		else if (input == "diplomacy") {
			cout << "Using diplomacy card" << endl;
			cout << "Please choose a victim" << endl;
			cout << "The available players are: ";
			for (std::map<string, Player*>::iterator it = players_Map.begin(); it != players_Map.end(); ++it) {
				cout << it->first << "  ";
			}
			string name;
			cin >> name;
			while (players_Map.find(name) == players_Map.end()) {
				cout << "No such player, are you kidding me?! Try again";
				cin >> name;
			}
			addOrder(new Negotiate(this, players_Map[name]));
			handOfCards->remove_CardinHand_ByType("diplomacy");


		}

		Order* o = orderList->getorderlist().back();
		
	        o->execute();
		
		orderList->getorderlist().pop_back();


		cout << "Are you done issuing orders? (Yes/No)" << endl;
		string s;
		cin >> s;
		if (s == "Yes" && reinforcement == 0) {
			finished = true;

		}

		
		return finished;
		
		//need to replace all to ps->issueOrder();
		
	}
}
