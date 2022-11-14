#include "GameEngine.h"
#include "Player.h"
//using namespace std;

//Constructor
GameEngine::GameEngine() {

	state_start = "Start";
	state_map_loaded = "Map Loaded";
	state_map_validated = "Map Validated";
	state_players_added = "Players Added";
	state_assign_reinforcement = "Assign Reinforcement";
	state_issue_orders = "Issue_Orders";
	state_execute_orders = "Execute Orders";
	state_win = "Win";
	state_Terminated = "Terminated";
	state = state_start;
	gameMap = nullptr;
	neutralPlayer = nullptr;
	deck = new Deck();

}
//Copy constructor
GameEngine::GameEngine(const GameEngine& copy) {

	state_start = copy.state_start;
	state_map_loaded = copy.state_map_loaded;
	state_map_validated = copy.state_map_validated;
	state_players_added = copy.state_players_added;
	state_assign_reinforcement = copy.state_assign_reinforcement;
	state_issue_orders = copy.state_issue_orders;
	state_execute_orders = copy.state_execute_orders;
	state_win = copy.state_win;
	state_Terminated = copy.state_Terminated;
	state = copy.state;
	gameMap = new Map(*copy.gameMap);
	neutralPlayer = new Player(*copy.neutralPlayer);

}

//Assignment operator overload
GameEngine&  GameEngine:: operator = (const GameEngine& copy) {
	state_start = copy.state_start;
	state_map_loaded = copy.state_map_loaded;
	state_map_validated = copy.state_map_validated;
	state_players_added = copy.state_players_added;
	state_assign_reinforcement = copy.state_assign_reinforcement;
	state_issue_orders = copy.state_issue_orders;
	state_execute_orders = copy.state_execute_orders;
	state_win = copy.state_win;
	state_Terminated = copy.state_Terminated;
	state = copy.state;
	gameMap = new Map(*copy.gameMap);
	neutralPlayer = new Player(*copy.neutralPlayer);

	return *this;

}

string GameEngine::getState()
{
	return state;
	
}

void GameEngine::setState(string newState)
{
	this->state = newState;
	Notify(this);
}

//Stream insersion operator
 ostream& operator << (ostream& out, const GameEngine& gameEngine) {
	 out << "Game_Engine";
	 return out;
}
string GameEngine::stringToLog() {
	return "Game Engine New State: " + getState();
}

void GameEngine::addPlayer(string playerName) {
	playerList.push_back(new Player(playerName));
}

void GameEngine::readMap(string mapName)
{
	MapLoader mapLoader;
	this->gameMap = mapLoader.readMap(mapName);
}

Player* GameEngine::getNeutralPlayer()
{
	if (this->neutralPlayer == nullptr)
		return new Player("Neutral");
	else
		return this->neutralPlayer;
}

void GameEngine::startupPhase() {
	//Load Map command
	map = MapLoader::readMap();
	while (map == nullptr) {
		cout << "No map is loaded. Please try again." << endl;
		map = MapLoader::readMap();
	}
	//Validate Map command  validate map code here

	//Add players sample to be modified
	playersList.push_back(new Player("faker"));
	playersList.push_back(new Player("uzi"));
	playersList.push_back(new Player("ikun"));

	//Game start command
	vector<Territory*> allTerritories = map -> getAllTerritories();

	//Distribute territories to players
	while (!allTerritories.empty()) {
		for (int i = 0; i < playersList.size(); i++) {
			playersList[i]->addTerritory(allTerritories.back());
			allTerritories.pop_back();
		}
	}
	//Creating random player order, this is the order of play
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(playersList), std::end(playersList), rng);

	//Assign reinforcement to each player
	for (int i = 0; i < playersList.size(); i++) {
		playersList[i]->setReinforcement(50);
		playersList[i]->set_all_territories(allTerritories);
	}

	for (int i = 0; i < playersList.size(); i++) {
		for (int j = 0; i < 2; j++) {
			playersList[i]->gethandofcard()->add_CardinHand(deck->draw());
		}
	}
   //End of Startup Phase 
	startupFinished = true;
}

void GameEngine::mainGameLoop() {

	if (!startupFinished) {
		cout << "Need to complete the startup phase first before entering the main loop !";
		return;
	}
	//Reinforcement phase
	
	vector<Continent*> continents = map->getAllContinents();

	while (playersList.size() > 1) {

		for (int i = 0; i < playersList.size(); i++) {
			//Assign troops based on the number of territories

			int num_Troop = 3;
			int num_Troop_base;
			Player* player = playersList[i];
			vector<Territory*> playerTerritories = player->getTerritories();

			num_Troop_base = playerTerritories.size() / 3;

			if (num_Troop_base > 3) {
				num_Troop = num_Troop_base;
			}

			//Assign continent bonus
			Continent* null_Continent = nullptr;
			for (int i = 0; i < continents.size(); i++) {
				if (continents[i] != nullptr) {
					bool control_continent = true;
					vector<Territory*> continent_territories = continents[i]->getTerritories();
					for (int k = 0; k < continent_territories.size(); k++) {
						if (!Utilities::find_Territory(playerTerritories, continent_territories[i])) {
							control_continent = false;
							break;
						}
					}
					if (control_continent) {

						num_Troop += continents[i]->getBonus();
						continents[i] = null_Continent;
					}


				}
			}

			player->setReinforcement(num_Troop);

		}

		vector<bool> issue_order_status;
		vector<bool> player_deployment_status;

		//Issue Order Phase
		for (int i = 0; i < playersList.size(); i++) {

			issue_order_status.push_back(false);
			player_deployment_status.push_back(false);

		}
		//Deployment orders only until all players are done
		while (Utilities::find_Bool(player_deployment_status, false)) {
			for (int i = 0; i < playersList.size(); i++) {

				if (player_deployment_status[i] != true) {
					if (playersList[i]->getReinforcement() != 0) {
						playersList[i]->issueOrder("Deploy");
					}
					else {
						player_deployment_status[i] = true;

					}
				}
			}
		}


		//Other orders
		while (Utilities::find_Bool(issue_order_status, false)) {
			for (int i = 0; i < playersList.size(); i++) {
				bool b = false;
				if (issue_order_status[i] != true) {

					b = playersList[i]->issueOrder("Any");
					issue_order_status[i] = b;
				}
			}
		}

		for (int i = 0; i < playersList.size(); i++) {
			Player* p = playersList[i];
			if (p->getTerritories().empty()) {
				delete(p);
				playersList.erase(playersList.begin() + i);
				i--;
			}
		}

	}

	cout << "The game has ended, the winner is  " << playersList[0]->getName() << endl;

}
	
	
