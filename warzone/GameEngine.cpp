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
	
