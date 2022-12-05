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

// PlayerStrategy Base Class
//----------------------------------------------------------
PlayerStrategy::PlayerStrategy(Player* player)
{
	this->p = player;
}
Player* PlayerStrategy::getPlayer() {
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
	//bool finished = false;
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
		/*while (std::find(p->getTerriotory().begin(),p->getTerriotory().end(),) {
			cout << "Wrong name, please try again." << endl;
			cin >> name;
		}*/

		cout << "Order type: Deploy " << num << " -> " << name << endl;

		p->setReinforcement(p->getReinforcement() - num);
		
		p->addOrder(new Deploy(num, this->p, p->getDeploy_territories()[name]));

		//Execute order
		Order* o = p->getlist()->getorderlist().back();
		
	        o->execute();
		
		p->getlist()->getorderlist().pop_back();
	}
	else if (orderName == "bomb") {
			cout << "Using the bomb card, please choose a territory" << endl;
			cout << "Available territories are: ";
			for (auto t :toAttack()){
				cout << t->getName() << "  ";
			}
			string target_name;
			cin >> target_name;
			while (p->getAvailable_territories().find(target_name) == p->getAvailable_territories().end()) {
				cout << "Wrong name, please try again." << endl;
				cin >> target_name;
			}
			p->addOrder(new Bomb(this->p, p->getAvailable_territories()[target_name], 0));
			p->getlist()->getorderlist().back()->execute();
			p->gethandofcard()->remove_CardinHand_ByType("bomb");
		}
		else if (orderName == "diplomacy") {
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
			p->getlist()->getorderlist().back()->execute();
			p->gethandofcard()->remove_CardinHand_ByType("diplomacy");
		}
		else if (orderName == "blockade") {
			cout << "Using the bomb card, please choose one of your territory" << endl;
			cout << "Available territories are: ";
			for (auto t : p->getTerriotory())
			cout << t->getName() << "  ";
			cout << endl;
			string target_name;
			cin >> target_name;
			while (p->getDeploy_territories().find(target_name) == p->getDeploy_territories().end()) {
				cout << "Wrong name, please try again." << endl;
				cin >> target_name;
			}
			p->addOrder(new Blockade(this->p, p->getAvailable_territories()[target_name]));
			p->getlist()->getorderlist().back()->execute();
			p->gethandofcard()->remove_CardinHand_ByType("blockade");
		}
	else if (orderName == "airlift") {
			cout << "Using this airlift card" << endl;
			cout << "Your territories are: ";
			for (auto t : p->getTerriotory())
			cout << t->getName() << "  ";
			cout << endl;
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
			for (auto t : p->getTerriotory())
			cout << t->getName() << "  ";
			cout << endl;
			string target_name;
			cin >> target_name;
			while (p->getDeploy_territories().find(target_name) == p->getDeploy_territories().end()) {
				cout << "Wrong name, please try again." << endl;
				cin >> target_name;
			}
			
			p->addOrder(new Airlift(this->p, p->getDeploy_territories()[source_name], p->getDeploy_territories()[target_name]));
			p->getlist()->getorderlist().back()->execute();
			p->gethandofcard()->remove_CardinHand_ByType("airlift");
		}
	else if (orderName == "Advance"){
		vector<string> Order_names;
		Order_names.push_back("Advance");
		vector<Card*> cards = p->gethandofcard()->get_VectorOfHand();
		for (int i = 0; i < cards.size(); i++) {
			Order_names.push_back(cards[i]->get_cardType());
		}
		
			cout << "Your territories are: "<<endl;
			for (auto t : p->getTerriotory()){
				cout << t->getName() << "  ";
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
			for (auto t :toAttack()){
				cout << t->getName() << "  ";
			}
			cout << endl;
			string target_name;
			cin >> target_name;
			while (p->getAvailable_territories().find(target_name) == p->getAvailable_territories().end()) {
				cout << "Wrong name, please try again." << endl;
				cin >> target_name;
			}
     	p->addOrder(new Advance(p->getDeploy_territories()[source_name], p->getAvailable_territories()[target_name], this->p, num));
		p->getlist()->getorderlist().back()->execute();
	}
	else{
		cout<<"invalid order name, please enter again!"<<endl;
	}
}

vector<Territory*> HumanPlayerStrategy::toAttack(){
	vector<Territory*> bannedTerritory;
	for (int i = 0; i < p->getAttackBan().size(); i++) {
		vector<Territory*> each_ban_player_tero = p->getAttackBan()[i]->getTerriotory();
		for (int k = 0; k < each_ban_player_tero.size(); k++) {
			bannedTerritory.push_back(each_ban_player_tero.at(k));
			}
		}
	
	vector<Territory*> toAttack;
for (Territory* t : p->getTerriotory()) {
		for (Territory* a : t->getNeighbours()) {
			if (!p->ownsTerritory(a)) {
				toAttack.push_back(a);
			}
		}
	}
	//toattack remove duplicate
	sort(toAttack.begin(),toAttack.end());
	toAttack.erase(unique(toAttack.begin(), toAttack.end()), toAttack.end());
	return toAttack;
}
vector<Territory*> HumanPlayerStrategy::toDedend(){
    return this->p->getTerriotory();
}

// AggressivePlayerStrategy
//----------------------------------------------------------
AggressivePlayerStrategy::AggressivePlayerStrategy(Player *player) : PlayerStrategy(player)
{
	strategyName = "Aggressive Player";
}
string AggressivePlayerStrategy::getStrategyName()
{
	return this->strategyName;
}

void AggressivePlayerStrategy::issueOrder(string orderName)
{
	p->set_Deploy_Territories();
	p->set_Available_Territories();
	if (orderName == "Deploy" || orderName == "Advance" || orderName == "bomb")
	{
		if (orderName == "Deploy")
		{
			cout << "\n********** " << p->getName() << "'s turn to deploy **********\n";
			if (p->getReinforcement() > 0)
			{
				p->addOrder(new Deploy(p->getReinforcement(), p, toDedend().at(0)));
				Order *o = p->getlist()->getorderlist().back();
				o->execute();
				p->getlist()->getorderlist().pop_back();
			}
			else
			{
				std::cout << "the pool is 0,cannot deploy" << endl;
			}
		}
		else if (orderName == "Advance")
		{
			bool check23 = true;
			while (check23)
			{
				if(toAttack().size()==0)
				  break;
				vector<Territory *> strong_can_attack;
				int count = 0;
				// where the strongest tero can attack
				if (toDedend().at(0)->getNeighbours().size() == 0)
				{
					if (toAttack().size() != 0)
						toDedend().at(0)->addNeighbour(toAttack().at(0)); // add a neibor for strongest
				}

				Territory *k = toAttack().at(0);
				Order *o = new Advance(p->toDefend().at(0), toAttack().at(0), this->p, p->toDefend().at(0)->getNumberOfArmies());
				o->execute();
				if (k->getOwner() != p || p->getDeploy_territories().size() == 50)
				{
					check23 = false;
				}
				else
				{
					if (k->getNumberOfArmies() == 0)
						check23 = false;
				}
			}
		}
		else if (orderName == "bomb")
		{
			cout << "Using the bomb card, please choose a territory" << endl;
			cout << "Available territories are: " << endl;

			for (int i = 0; i < toAttack().size(); i++)
			{
				cout << toAttack().at(i)->getName() << "  ";
			}
			string target_name;
			bool check3 = true;
			int recorddd;
			while (check3) // check whether true input
			{
				cin >> target_name;
				for (int i = 0; i < toAttack().size(); i++)
				{
					if (target_name == toAttack().at(i)->getName())
					{
						check3 = false;
						recorddd = i;
					}
				}
				if (check3)
				{
					cout << "error name,please choose a territory to use bomb from the list" << endl;
				}
			}
			cout << "The territory to use bomb from the list is: " << target_name << endl;
			Order *o = new Bomb(p, p->toAttack().at(recorddd), 0);
			// Execute order
			o->execute();
		}
	}
	else
	{
		if (orderName == "airlift")
		{
			std::cout << "AggressivePlayerStrategy doesnt airlift." << endl;
		}
		else if (orderName == "diplomacy")
		{
			std::cout << "AggressivePlayerStrategy doesnt diplomacy." << endl;
		}
		else if (orderName == "blockade")
		{
			std::cout << "AggressivePlayerStrategy doesnt blockade." << endl;
		}
	}
}
vector<Territory *> AggressivePlayerStrategy::toAttack()
{
	vector<Territory *> bannedTerritory;
	for (int i = 0; i < p->getAttackBan().size(); i++)
	{
		vector<Territory *> each_ban_player_tero = p->getAttackBan()[i]->getTerriotory();
		for (int k = 0; k < each_ban_player_tero.size(); k++)
		{
			bannedTerritory.push_back(each_ban_player_tero.at(k)); // cannot attact not dulicate
		}
	}

	vector<Territory *> toAttack;
	for (Territory *t : p->getTerriotory())
	{
		for (Territory *a : t->getNeighbours())
		{
			if (!p->ownsTerritory(a))
			{
				toAttack.push_back(a);
			}
		}
	}
	sort(toAttack.begin(), toAttack.end());
	toAttack.erase(unique(toAttack.begin(), toAttack.end()), toAttack.end());
	for (int i = 0; i < toAttack.size(); i++)
	{
		for (int k = 0; k < bannedTerritory.size(); k++)
		{
			if (toAttack.at(i) == bannedTerritory.at(k))
				toAttack.erase(toAttack.begin() + i);
		}
	}
	//}
	return toAttack;
}
vector<Territory *> AggressivePlayerStrategy::toDedend()
{
	int smallest = 0;
	int record = 0;
	vector<Territory *> deplicate = p->getTerriotory();
	for (int k = 0; k < deplicate.size(); k++)
	{
		if (deplicate.at(k)->getNumberOfArmies() > smallest)
		{
			smallest = deplicate.at(k)->getNumberOfArmies();
			record = k;
		}
	}
	Territory *swap1 = deplicate.at(0);
	Territory *swap2 = deplicate.at(record);
	deplicate.at(0) = swap2;
	deplicate.at(record) = swap1; // the first one is always the strongest
	return deplicate;
}

// BenevolentPlayerStrategy
//----------------------------------------------------------

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *player) : PlayerStrategy(player)
{
	strategyName = "Benevolent  Player";
}
string BenevolentPlayerStrategy::getStrategyName()
{
	return this->strategyName;
}

 
void BenevolentPlayerStrategy::issueOrder(string orderName)
{
	if (orderName == "Deploy")
	{
		cout << "\n********** " << p->getName() << "'s turn to deploy **********\n";
		if (p->getReinforcement() > 0)
		{
			Order *o = new Deploy(p->getReinforcement(), p, toDedend().at(0));
			p->setReinforcement(0);
			// Execute order
			o->execute();
		}
	}
	else if (orderName == "Advance" || orderName == "bomb")
	{
		if (orderName == "Advance")
		{

		}
	}
}
vector<Territory *> BenevolentPlayerStrategy::toAttack()
{
	// never attack
	cout << "cannot attack,return empty default vector" << endl;
	vector<Territory *> empty;
	return empty;
}
vector<Territory *> BenevolentPlayerStrategy::toDedend()
{
	int smallest = 10000000;
	int record = 0;
	vector<Territory *> deplicate = p->getTerriotory();
	for (int k = 0; k < deplicate.size(); k++)
	{
		if (deplicate.at(k)->getNumberOfArmies() < smallest)
		{
			smallest = deplicate.at(k)->getNumberOfArmies();
			record = k;
		}
	}
	Territory *swap1 = deplicate.at(0);
	Territory *swap2 = deplicate.at(record);
	deplicate.at(0) = swap2;
	deplicate.at(record) = swap1; // the first one is always the weakest
	return deplicate;
}
// NeutralPlayerStrategy
//----------------------------------------------------------
NeutralPlayerStrategy::NeutralPlayerStrategy(Player *player) : PlayerStrategy(player)
{
	strategyName = "Neutral Player";
}
string NeutralPlayerStrategy::getStrategyName()
{
	return this->strategyName;
}

void NeutralPlayerStrategy::issueOrder(string orderName)
{
	if(orderName == "Deploy")
		cout << "\n********** " << p->getName() << "'s turn to deploy **********\n";
	if (!p->getifattacked())
	{
		//This is a Neutral Player, it cannot issue any Order, becasue it hasnt been attacked
	}
	if (p->getifattacked())
	{
		// Neutral Player was attacked, it will become an Aggressive player
		p->setPlayerStrategy(new AggressivePlayerStrategy(p));
		p->issueOrder(orderName);
	}
}

vector<Territory *> NeutralPlayerStrategy::toAttack()
{
	vector<Territory *> toAttack;
	return toAttack;
}
vector<Territory *> NeutralPlayerStrategy::toDedend()
{
	return p->getTerriotory();
}
//CheaterPlayerStrategy (Done)
//----------------------------------------------------------
CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player):PlayerStrategy (player){
    strategyName ="Cheater Player";
}
string CheaterPlayerStrategy::getStrategyName(){
    return this->strategyName;
}

//Once CheaterPlayer issues Order, it automatically conquers that are adjacent to its own territories
void CheaterPlayerStrategy:: issueOrder(string orderName){

	if (orderName == "Deploy")
		cout << "\n********** " << p->getName() << "'s turn to deploy **********\n";
	else if(orderName == "Advance")
	{
		vector<Territory*> enemy_territories = toAttack();
		for (Territory* t : enemy_territories) {
			if (t->getOwner() != p) {
				t->getOwner()->deleteTerriotory(t);
				t->setOwner(p);
				p->addTerritory(t);
			}
		}
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
	sort(toAttack.begin(),toAttack.end());
	toAttack.erase(unique(toAttack.begin(), toAttack.end()), toAttack.end());
	return toAttack;
}
vector<Territory*> CheaterPlayerStrategy::toDedend(){
	return p->getTerriotory();
}
