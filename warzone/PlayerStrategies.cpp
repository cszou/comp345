#include "PlayerStrategies.h"
#include "Player.h"
#include <iostream>
#include <string>
#include "Orders.h"
#include "Card.h"
#include "Map.h"
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

//PlayerStrategy Base Class
//----------------------------------------------------------
PlayerStrategy::PlayerStrategy(Player* player){
    this->p = player;
}
Player* PlayerStrategy::getPlayer(){
	return p;
}

//HumanPlayerStrategy
//----------------------------------------------------------
HumanPlayerStrategy::HumanPlayerStrategy(Player* player):PlayerStrategy (player){
     strategyName = "Human Player";
}

void HumanPlayerStrategy::issueOrder(string orderName)
{
	p->set_Deploy_Territories();
	p->set_Available_Territories();
	cout << "Order Issuing phase for player " << strategyName << endl;
	bool finished = false;
	//Case deploy
	if (orderName == "Deploy") {
		cout << "Please enter a deployement order" << endl;
		cout << "Your territories are: ";
		for (auto t : p->getTerriotory())
			cout << t->getName() << "  ";
		cout << endl;
		cout << "You have " << p->getReinforcement() << " troops left in your reinforcement tool, please enter the number of troops you want to use" << endl;
		int num;
		cin >> num;
		while (!cin) {
			cout << "Wrong data type. Please try again. " << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> num;
		}
		if (num > p->getReinforcement()) {
			num = p->getReinforcement();
		}
		cout << "Where do you want to deploy " << num << " troops? Please enter the name of the territory. " << endl;
		string name;
		cin >> name;
		while (p->getDeploy_territories().find(name) == p->getDeploy_territories().end()) {
			cout << "Wrong name, please try again." << endl;
			cin >> name;
		}
		cout << "Order type: Deploy " << num << " -> " << name << endl;

		p->setReinforcement(p->getReinforcement() - num);
		
		p->addOrder(new Deploy(num, this->p, p->getDeploy_territories()[name]));

		//Execute order
		Order* o = p->getlist()->getorderlist().back();
		
	        o->execute();
		
		p->getlist()->getorderlist().pop_back();



		cout << "Are you done issuing orders? (Yes/No)" << endl;
		string s;
		cin >> s;
		if (s == "Yes" && p->getReinforcement() == 0) {
			finished = true;

		}

	}
	else {
		//Other case
		vector<string> Order_names;
		Order_names.push_back("Advance");
		vector<Card*> cards = p->gethandofcard()->get_VectorOfHand();
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
			for (std::map<string, Territory*>::iterator it = p->getDeploy_territories().begin(); it != p->getDeploy_territories().end(); ++it) {

				cout << it->first << "  ";

			}
			cout << endl;
			cout << "Choose the source territory: ";
			string source_name;
			cin >> source_name;
			while (p->getDeploy_territories().find(source_name) == p->getDeploy_territories().end()) {
				cout << "Wrong name, please try again." << endl;
				cin >> source_name;
			}
			int army_num = p->getDeploy_territories()[source_name]->getNumberOfArmies();
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
			for (std::map<string, Territory*>::iterator it = p->getAvailable_territories().begin(); it != p->getAvailable_territories().end(); ++it) {

				cout << it->first << "  ";

			}
			cout << endl;
			string target_name;
			cin >> target_name;
			while (p->getAvailable_territories().find(target_name) == p->getAvailable_territories().end()) {
				cout << "Wrong name, please try again." << endl;
				cin >> target_name;
			}
			p->addOrder(new Advance(p->getDeploy_territories()[source_name], p->getAvailable_territories()[target_name], this->p, num));


		}

		//Bomb card
		else if (input == "bomb") {
			cout << "Using the bomb card, please choose a territory" << endl;
			cout << "Available territories are: ";
			for (std::map<string, Territory*>::iterator it = p->getAvailable_territories().begin(); it != p->getAvailable_territories().end(); ++it) {

				cout << it->first << "  ";

			}
			string target_name;
			cin >> target_name;
			while (p->getAvailable_territories().find(target_name) == p->getAvailable_territories().end()) {
				cout << "Wrong name, please try again." << endl;
				cin >> target_name;
			}
			p->addOrder(new Bomb(this->p, p->getAvailable_territories()[target_name], 0));
			p->gethandofcard()->remove_CardinHand_ByType("bomb");
		}



		if (input == "blockade") {
			cout << "Using the bomb card, please choose one of your territory" << endl;
			cout << "Available territories are: ";
			for (std::map<string, Territory*>::iterator it =p->getDeploy_territories().begin(); it != p->getDeploy_territories().end(); ++it) {

				cout << it->first << "  ";

			}
			string target_name;
			cin >> target_name;
			while (p->getDeploy_territories().find(target_name) == p->getDeploy_territories().end()) {
				cout << "Wrong name, please try again." << endl;
				cin >> target_name;
			}
			p->addOrder(new Blockade(this->p, p->getAvailable_territories()[target_name]));
			p->gethandofcard()->remove_CardinHand_ByType("blockade");
		}

		//Air Lift
		else if (input == "airlift") {
			cout << "Using this airlift card" << endl;
			cout << "Your territories are: ";
			for (std::map<string, Territory*>::iterator it = p->getDeploy_territories().begin(); it != p->getDeploy_territories().end(); ++it) {

				cout << it->first << "  ";

			}
			cout << "Choose the source territory";
			string source_name;
			cin >> source_name;
			while (p->getDeploy_territories().find(source_name) == p->getDeploy_territories().end()) {
				cout << "Wrong name, please try again." << endl;
				cin >> source_name;
			}
			int army_num = p->getDeploy_territories()[source_name]->getNumberOfArmies();
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
			for (std::map<string, Territory*>::iterator it = p->getDeploy_territories().begin(); it != p->getDeploy_territories().end(); ++it) {

				cout << it->first << "  ";

			}
			string target_name;
			cin >> target_name;
			while (p->getDeploy_territories().find(target_name) == p->getDeploy_territories().end()) {
				cout << "Wrong name, please try again." << endl;
				cin >> target_name;
			}
			
			p->addOrder(new Airlift(this->p, p->getDeploy_territories()[source_name], p->getDeploy_territories()[target_name]));
			p->gethandofcard()->remove_CardinHand_ByType("airlift");
		}
		else if (input == "diplomacy") {
			cout << "Using diplomacy card" << endl;
			cout << "Please choose a victim" << endl;
			cout << "The available players are: ";
			for (std::map<string, Player*>::iterator it =p->getPlayers_Map().begin(); it != p->getPlayers_Map().end(); ++it) {
				cout << it->first << "  ";
			}
			string name;
			cin >> name;
			while (p->getPlayers_Map().find(name) == p->getPlayers_Map().end()) {
				cout << "No such player, are you kidding me?! Try again";
				cin >> name;
			}
			p->addOrder(new Negotiate(this->p, p->getPlayers_Map()[name]));
			p->gethandofcard()->remove_CardinHand_ByType("diplomacy");


		}

		Order* o = p->getlist()->getorderlist().back();
		
	        o->execute();
		
		p->getlist()->getorderlist().pop_back();


		cout << "Are you done issuing orders? (Yes/No)" << endl;
		string s;
		cin >> s;
		if (s == "Yes" && p->getReinforcement() == 0) {
			finished = true;

		}
	}
}

vector<Territory*> HumanPlayerStrategy::toAttack(){
	vector<Territory*> bannedTerritory;
	for (int i = 0; i < p->getAttackBan().size(); i++) {
		vector<Territory*> player_territories = p->getAttackBan()[i]->getTerriotory();
		for (int k = 0; k < player_territories.size(); k++) {
			Territory* t = player_territories[k];
			if (find(bannedTerritory.begin(), bannedTerritory.end(), t) == bannedTerritory.end()) {
				bannedTerritory.push_back(t);
			}
		}
	}
	vector<Territory*> tAttack;
	for (int i = 0; i < p->getTerriotory().size(); i++) {
		vector<Territory*> neignbours = p->getTerriotory()[i]->getNeighbours();
		for (int k = 0; k < neignbours.size(); k++) {
			if ((find(tAttack.begin(), tAttack.end(), neignbours[k]) == tAttack.end())
				&& find(bannedTerritory.begin(), bannedTerritory.end(), neignbours[k]) == bannedTerritory.end())
			{
				tAttack.push_back(neignbours[k]);
			}
		}
	}
	for (int i = 0; i < p->getTerriotory().size(); i++) {
		if (find(tAttack.begin(), tAttack.end(), p->getTerriotory()[i]) == tAttack.end()) {
			tAttack.push_back(p->getTerriotory()[i]);
		}
	}
	return tAttack;

}
vector<Territory*> HumanPlayerStrategy::toDedend(){
    return this->p->getTerriotory();
}
//AggressivePlayerStrategy 
//----------------------------------------------------------
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player):PlayerStrategy (player){
    strategyName = "Aggressive Player";
}	
string AggressivePlayerStrategy::getStrategyName() {
	return this->strategyName;
}

void AggressivePlayerStrategy::issueOrder(string OrderName) {
	cout << "Excecuting isssue order from " << getStrategyName() << endl;
	//deploys or advances armies on its strongest 	country, then always advances to enemy territories
	
	p->set_Deploy_Territories();
	p->set_Available_Territories();
	//1. deploy phase
	
		cout << "deploy phase, deploy to strongest country" << endl;
		cout << "Your territories are: ";
		for (auto t : p->getTerriotory())
			cout << t->getName() << "  ";
		cout << endl;
		cout  << p->getReinforcement() << " troops left in your reinforcement tool, max troop will be used" << endl;
		int num = p->getReinforcement();
		
		cout <<  num << " tropp will be deployed on the strongest country " << endl;
		
		string name = toDedend().at(0)->getName();
		
		
		cout << "Order type: Deploy " << num << " -> " << name << endl;

		p->setReinforcement(p->getReinforcement() - num);

		p->addOrder(new Deploy(num, this->p, p->getDeploy_territories()[name]));

		//Execute order
		Order* o = p->getlist()->getorderlist().back();

		o->execute();

		p->getlist()->getorderlist().pop_back();

	

		//2. Advance phase
		cout << "advance phase, always advance to enemy" << endl;
		
			cout << "Your territories are: ";
			for (std::map<string, Territory*>::iterator it = p->getDeploy_territories().begin(); it != p->getDeploy_territories().end(); ++it) {

				cout << it->first << "  ";

			}
			cout << endl;
			
			string source_name = toDedend().at(0)->getName();
			
			
			int army_num = p->getDeploy_territories()[source_name]->getNumberOfArmies();
			cout << army_num << " will advance to enemy territory " << endl;

			int num = army_num;
			
			
			cout << "Available territories are: ";
			for (std::map<string, Territory*>::iterator it = p->getAvailable_territories().begin(); it != p->getAvailable_territories().end(); ++it) {

				cout << it->first << "  ";

			}
			cout << endl;
			string target_name = toAttack().at(0)->getName();
			
			
			p->addOrder(new Advance(p->getDeploy_territories()[source_name], p->getAvailable_territories()[target_name], this->p, num));


	//3. card playing phase only playing aggressive cards
		cout << "playing cards" << endl;
		cout << "Using the bomb card, please choose a territory" << endl;
		cout << "Available territories are: ";
		for (std::map<string, Territory*>::iterator it = p->getAvailable_territories().begin(); it != p->getAvailable_territories().end(); ++it) {

			cout << it->first << "  ";

		}
		string target_name=toAttack.at(0)->getName();
		
		p->addOrder(new Bomb(this->p, p->getAvailable_territories()[target_name], 0));
		p->gethandofcard()->remove_CardinHand_ByType("bomb");

		
}
vector<Territory*> AggressivePlayerStrategy::toAttack() {
	vector<Territory*> bannedTerritory;
	for (int i = 0; i < p->getAttackBan().size(); i++) {
		vector<Territory*> player_territories = p->getAttackBan()[i]->getTerriotory();
		for (int k = 0; k < player_territories.size(); k++) {
			Territory* t = player_territories[k];
			if (find(bannedTerritory.begin(), bannedTerritory.end(), t) == bannedTerritory.end()) {
				bannedTerritory.push_back(t);
			}
		}
	}
	vector<Territory*> tAttack;
	for (int i = 0; i < p->getTerriotory().size(); i++) {
		vector<Territory*> neignbours = p->getTerriotory()[i]->getNeighbours();
		for (int k = 0; k < neignbours.size(); k++) {
			if ((find(tAttack.begin(), tAttack.end(), neignbours[k]) == tAttack.end())
				&& find(bannedTerritory.begin(), bannedTerritory.end(), neignbours[k]) == bannedTerritory.end())
			{
				tAttack.push_back(neignbours[k]);
			}
		}
	}
	for (int i = 0; i < p->getTerriotory().size(); i++) {
		if (find(tAttack.begin(), tAttack.end(), p->getTerriotory()[i]) == tAttack.end()) {
			tAttack.push_back(p->getTerriotory()[i]);
		}
	}
	return tAttack;
	}
vector<Territory*> AggressivePlayerStrategy::toDedend() {
	return p->getTerriotory();
	}

//BenevolentPlayerStrategy 
//----------------------------------------------------------
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player):PlayerStrategy (player){
    strategyName = "Benevolent Player";
}
	
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) : PlayerStrategy(player) {
	strategyName = "BenevolentPlayer";
}
string NeutralPlayerStrategy::getStrategyName() {
	return this->strategyName;
}

void BenevolentPlayerStrategy::issueOrder(string OrderName) {
	cout << "Excecuting isssue order from " << getStrategyName() << endl;
	//otecting its weak countries(deploys or advances armieson its weakest countries
	// //deploys or advances armies on its strongest 	country, then always advances to enemy territories
	p->set_Deploy_Territories();
	p->set_Available_Territories();
	//1. deploy phase

	cout << "deploy phase, deploy to protect weakest countries" << endl;
	cout << "Your territories are: ";
	for (auto t : p->getTerriotory())
		cout << t->getName() << "  ";
	cout << endl;
	cout << p->getReinforcement() << " troops left in your reinforcement tool, max troop will be used" << endl;
	int num = p->getReinforcement();

	cout << num << " tropp will be deployed on the weakest country " << endl;

	string name = toDedend().at(0)->getName();


	cout << "Order type: Deploy " << num << " -> " << name << endl;

	p->setReinforcement(p->getReinforcement() - num);

	p->addOrder(new Deploy(num, this->p, p->getDeploy_territories()[name]));

	//Execute order
	Order* o = p->getlist()->getorderlist().back();

	o->execute();

	p->getlist()->getorderlist().pop_back();


		//no advance phaseNEVER ADVANCE TO ENEMY TERRITORY
	cout << "no advance phase " << endl;
	//2. may use cards (no bomb)
	cout << "card playing phase" << endl;
	int input = rand()%3 + 1;
	//blockade
	if (input == 1) {
		cout << "Using the blockade card, the target territory is chose automatically" << endl;
		cout << "Available territories are: ";
		for (std::map<string, Territory*>::iterator it = p->getDeploy_territories().begin(); it != p->getDeploy_territories().end(); ++it) {

			cout << it->first << "  ";

		}
		string target_name=toAttack.at(0)->getName();
		
		p->addOrder(new Blockade(this->p, p->getAvailable_territories()[target_name]));
		p->gethandofcard()->remove_CardinHand_ByType("blockade");
	}

	//Air Lift
	else if (input == 2) {
		cout << "Using this airlift card" << endl;
		cout << "Your territories are: ";
		for (std::map<string, Territory*>::iterator it = p->getDeploy_territories().begin(); it != p->getDeploy_territories().end(); ++it) {

			cout << it->first << "  ";

		}
		cout << "the source territory is chosen automatically";
		string source_name=toDedend.at(0)->getName();
		
		
		int army_num = p->getDeploy_territories()[source_name]->getNumberOfArmies();
		cout << "You have " << army_num << "army unites in this territory, max will be moved" << endl;

		int num=army_num;
		
		cout << "the target territory is chosen automatically" << endl;
		cout << "The available options are your territories and the enemy territories" << endl;
		cout << "Available territories are: ";
		for (std::map<string, Territory*>::iterator it = p->getDeploy_territories().begin(); it != p->getDeploy_territories().end(); ++it) {

			cout << it->first << "  ";

		}
		string target_name=toAttack.at(0)->getName();
		

		p->addOrder(new Airlift(this->p, p->getDeploy_territories()[source_name], p->getDeploy_territories()[target_name]));
		p->gethandofcard()->remove_CardinHand_ByType("airlift");
	}
	//diplomacy
	else if (input == 3) {
		cout << "Using diplomacy card" << endl;
		cout << "a victim is chosen automatically" << endl;
		cout << "The available players are: ";
		for (std::map<string, Player*>::iterator it = p->getPlayers_Map().begin(); it != p->getPlayers_Map().end(); ++it) {
			cout << it->first << "  ";
		}
		string name= p->getName();
		
		
		p->addOrder(new Negotiate(this->p, p->getPlayers_Map()[name]));
		p->gethandofcard()->remove_CardinHand_ByType("diplomacy");


	}

	Order* o = p->getlist()->getorderlist().back();

	o->execute();

	p->getlist()->getorderlist().pop_back();
	
		
	}

	//benevolent player don't attack
	vector<Territory*> BenevolentPlayerStrategy::toAttack()
	{
		vector<Territory*> null;
		return null;
	}
	vector<Territory*> BenevolentPlayerStrategy::toDedend() {
		return p->getTerriotory();
	}


//NeutralPlayerStrategy
//----------------------------------------------------------
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player):PlayerStrategy (player){
    strategyName ="Neutral Player";
}
string NeutralPlayerStrategy::getStrategyName(){
    return this->strategyName;
}

void NeutralPlayerStrategy:: issueOrder(string orderName){

    cout<<"Excecuting isssue order from "<<getStrategyName()<<endl;

	if(p->getifattacked()){
	cout<<"This is a Neutral Player, it cannot issue any Order "<<endl;
	}
	
	if(!p->getifattacked()){
	cout<<"Neutral Player is attacked, it will become an Aggressive player."<<endl;
    p->setPlayerStrategy(new AggressivePlayerStrategy(p));
	p->issueOrder(orderName);
	}

}

vector<Territory*> NeutralPlayerStrategy::toAttack(){
	vector<Territory*> toAttack;
	return toAttack;
}
vector<Territory*> NeutralPlayerStrategy::toDedend(){
	return p->getTerriotory();
}

//CheaterPlayerStrategy
//----------------------------------------------------------
CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player):PlayerStrategy (player){
    strategyName ="Cheater Player";
}
string CheaterPlayerStrategy::getStrategyName(){
    return this->strategyName;
}

//Once CheaterPlayer issues Order, it automatically conquers that are adjacent to its own territories
void CheaterPlayerStrategy:: issueOrder(string orderName){
	cout<<"Excecuting isssue order from "<<getStrategyName()<<endl;
	cout<<getStrategyName()<<" will conquer all territories that are adjacent to its own!"<<endl;
	cout<<"My adjacent territories are: "<<endl;
	for (Territory* t :toAttack()){
		cout<<t->getName()<<"  ";
		t->setOwner(this-> p);
	}

	cout<<"After conquering, My territories are: "<<endl;
	for (Territory* t :p->getTerriotory()){
		cout<<t->getName()<<"  ";
	}

}

//return all adjacent territories 
vector<Territory*> CheaterPlayerStrategy::toAttack(){
	vector<Territory*> toAttack;
	for (Territory* t : p->getTerriotory()) {
		for (Territory* a : t->getNeighbours()) {
			if (!p->ownsTerritory(a)) {
				toAttack.push_back(a);
			}
		}
	}
	for (Territory* t : toAttack) {
		toAttack.erase(unique(toAttack.begin(), toAttack.end()), toAttack.end());
	}
}
vector<Territory*> CheaterPlayerStrategy::toDedend(){
	return p->getTerriotory();
}

