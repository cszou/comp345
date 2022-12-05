#include "GameEngineDriver.h"
#include "GameEngine.h"
#include "Player.h"
#include <iostream>
using std::cin;
using std::cout;
#include <string>
using std::string;
#include <vector>
using std::vector;

void testStartupPhase() {

	GameEngine* game = new GameEngine();
	//Load Map command
	string mapName;
	cout << "Please enter the map name: ";
	cin >> mapName;
	game->map = MapLoader::readMap(mapName);
	while (game->map == nullptr) {
		cout << "No map is loaded. Please try again." << endl;
		cout << "Please enter the map name: ";
		cin >> mapName;
		game->map = MapLoader::readMap(mapName);
	}
	//Validate Map command  validate map code here

	//Add players sample to be modified
	game->playersList.push_back(new Player("faker"));
	game->playersList.push_back(new Player("uzi"));
	game->playersList.push_back(new Player("ikun"));

	//Game start command
	vector<Territory*> allTerritories = game->map->getAllTerritories();

	//Distribute territories to players
	while (!allTerritories.empty()) {
		for (int i = 0; i < game->playersList.size(); i++) {
			if (allTerritories.empty())
				break;
			game->playersList[i]->addTerritory(allTerritories.back());
			allTerritories.pop_back();
		}
	}

	//Creating random player order, this is the order of play
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(game->playersList), std::end(game->playersList), rng);

	//Assign reinforcement to each player
	for (int i = 0; i < game->playersList.size(); i++) {
		game->playersList[i]->setReinforcement(50);
		game->playersList[i]->set_all_territories(allTerritories);
	}

	for (int i = 0; i < game->playersList.size(); i++) {
		for (int j = 0; j < 2; j++) {
			game->playersList[i]->gethandofcard()->add_CardinHand(game->deck->draw());
		}
	}

	//End of Startup Phase 
	game->startupFinished = true;

	delete game;
}

void testMainGameLoop(Player* p1, Player* p2) {

	GameEngine* game = new GameEngine();
	game->startupFinished = true;
	game->readMap("europe.map");
	/*
	if (!game->startupFinished) {
		cout << "Need to complete the startup phase first before entering the main loop !";
		return;
	}*/
	//Reinforcement phase

	//Add players and get continents and territories
    //game->playersList.push_back(new Player("faker"));
	//game->playersList.push_back(new Player("uzi"));
	//game->playersList.push_back(new Player("ikun"));
	game->playersList.push_back(p1);
	game->playersList.push_back(p2);
	vector<Territory*> allTerritories = game->map->getAllTerritories();
	vector<Continent*> continents = game->map->getAllContinents();

	//Distribute territories to players
	while (!allTerritories.empty()) {
		for (int i = 0; i < game->playersList.size(); i++) {
			if (allTerritories.empty())
				break;
			Territory* t = allTerritories.back();
			game->playersList[i]->addTerritory(t);
			t->setOwner(game->playersList[i]);
			allTerritories.pop_back();
		}
	}

	while (game->playersList.size() > 1) {

		for (int i = 0; i < game->playersList.size(); i++) {
			//Assign troops based on the number of territories
			int num_Troop = 3;
			int num_Troop_base;
			Player* player = game->playersList[i];
			vector<Territory*> playerTerritories = player->getTerriotory();

			num_Troop_base = playerTerritories.size() / 3;

			if (num_Troop_base > 3) {
				num_Troop = num_Troop_base;
			}
			//Assign continent bonus
			Continent* null_Continent = nullptr;
			for (int j = 0; j < continents.size(); j++) {
				if (continents[j] != nullptr) {
					bool control_continent = true;
					vector<Territory*> continent_territories = continents[j]->getTerritories();
					for (int k = 0; k < continent_territories.size(); k++) {
						if (find(playerTerritories.begin(), playerTerritories.end(), continent_territories[k]) != playerTerritories.end()) {
							control_continent = false;
							break;
						}
					}
					if (control_continent) {

						num_Troop += continents[j]->getBonus();
						continents[j] = null_Continent;
					}
				}
			}
			player->setReinforcement(num_Troop);
		}

		vector<bool> issue_order_status;
		vector<bool> player_deployment_status;

		//Issue Order Phase
		for (int i = 0; i < game->playersList.size()-1; i++) {
			cout<<"Issue Order Phase"<<endl;
			issue_order_status.push_back(false);
			player_deployment_status.push_back(false);
		}
		
		//Deployment orders only until all players are done
		while (game->find_Bool(player_deployment_status, false)) {
			cout<<"Deployment orders"<<endl;
			for (int i = 0; i < game->playersList.size(); i++) {
				cout<<"Deployment orders"<<endl;
				if (player_deployment_status[0] != true) {
					if (game->playersList[0]->getReinforcement() != 0) {
						game->playersList[0]->issueOrder("Deploy");
					}
					else {
						player_deployment_status[0] = true;

					}
				}
			}
		}
		game->playersList[1]->issueOrder("Deploy");

		cout << 4 << endl;
		//Other orders
		
		while (game->find_Bool(issue_order_status, false)) {
			for (int i = 0; i < game->playersList.size(); i++) {
				bool b = false;
				if (issue_order_status[0] != true) {
					cout<<"Other orders"<<endl;
					b = true;//game->playersList[i]->issueOrder("Any");
					issue_order_status[0] = b;
				}
			}
		}
       game->playersList[1]->issueOrder("Deploy");
		for (int i = 0; i < game->playersList.size(); i++) {
			Player* p = game->playersList[i];
			if (p->getTerriotory().empty()) {
				delete(p);
				game->playersList.erase(game->playersList.begin() + i);
				i--;
			}
		}

	}

	cout << "The game has ended, the winner is  " << game->playersList[0]->getName() << endl;

}
