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
	game->playerList.push_back(new Player("faker"));
	game->playerList.push_back(new Player("uzi"));
	game->playerList.push_back(new Player("ikun"));

	//Game start command
	vector<Territory*> allTerritories = game->map->getAllTerritories();

	//Distribute territories to players
	while (!allTerritories.empty()) {
		for (int i = 0; i < game->playerList.size(); i++) {
			if (allTerritories.empty())
				break;
			game->playerList[i]->addTerritory(allTerritories.back());
			allTerritories.pop_back();
		}
	}

	//Creating random player order, this is the order of play
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(game->playerList), std::end(game->playerList), rng);

	//Assign reinforcement to each player
	for (int i = 0; i < game->playerList.size(); i++) {
		game->playerList[i]->setReinforcement(50);
		game->playerList[i]->set_all_territories(allTerritories);
	}

	for (int i = 0; i < game->playerList.size(); i++) {
		for (int j = 0; j < 2; j++) {
			game->playerList[i]->gethandofcard()->add_CardinHand(game->deck->draw());
		}
	}

	//End of Startup Phase 
	game->startupFinished = true;

	delete game;
}

void testMainGameLoop() {

	GameEngine* game = new GameEngine();
	game->startupFinished = true;
	game->readMap("europe.map");
	if (!game->startupFinished) {
		cout << "Need to complete the startup phase first before entering the main loop !";
		return;
	}
	//Reinforcement phase

	//Add players and get continents and territories
	game->playerList.push_back(new Player("faker"));
	game->playerList.push_back(new Player("uzi"));
	game->playerList.push_back(new Player("ikun"));
	vector<Territory*> allTerritories = game->map->getAllTerritories();
	vector<Continent*> continents = game->map->getAllContinents();

	//Distribute territories to players
	while (!allTerritories.empty()) {
		for (int i = 0; i < game->playerList.size(); i++) {
			if (allTerritories.empty())
				break;
			Territory* t = allTerritories.back();
			game->playerList[i]->addTerritory(t);
			t->setOwner(game->playerList[i]);
			allTerritories.pop_back();
		}
	}

	while (game->playerList.size() > 1) {

		for (int i = 0; i < game->playerList.size(); i++) {
			//Assign troops based on the number of territories
			int num_Troop = 3;
			int num_Troop_base;
			Player* player = game->playerList[i];
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
		for (int i = 0; i < game->playerList.size(); i++) {

			issue_order_status.push_back(false);
			player_deployment_status.push_back(false);

		}
		//Deployment orders only until all players are done
		while (game->find_Bool(player_deployment_status, false)) {
			for (int i = 0; i < game->playerList.size(); i++) {
				if (player_deployment_status[i] != true) {
					if (game->playerList[i]->getReinforcement() != 0) {
						game->playerList[i]->issueOrder("Deploy");
					}
					else {
						player_deployment_status[i] = true;

					}
				}
			}
		}

		cout << 4 << endl;
		//Other orders
		while (game->find_Bool(issue_order_status, false)) {
			for (int i = 0; i < game->playerList.size(); i++) {
				bool b = false;
				if (issue_order_status[i] != true) {

					b = game->playerList[i]->issueOrder("Any");
					issue_order_status[i] = b;
				}
			}
		}

		for (int i = 0; i < game->playerList.size(); i++) {
			Player* p = game->playerList[i];
			if (p->getTerriotory().empty()) {
				delete(p);
				game->playerList.erase(game->playerList.begin() + i);
				i--;
			}
		}

	}

	cout << "The game has ended, the winner is  " << game->playerList[0]->getName() << endl;

}
