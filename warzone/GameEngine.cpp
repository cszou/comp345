#include "GameEngine.h"
#include "Player.h"
//using namespace std;


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
	map = nullptr;
	neutralPlayer = nullptr;
	deck = new Deck();
	isTournamentMode = false;
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
	map = new Map(*copy.map);
	neutralPlayer = new Player(*copy.neutralPlayer);
	deck = new Deck(*copy.deck);
	isTournamentMode = copy.isTournamentMode;
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
	map = new Map(*copy.map);
	neutralPlayer = new Player(*copy.neutralPlayer);
	deck = new Deck(*copy.deck);
	isTournamentMode = copy.isTournamentMode;
	return *this;

}

GameEngine::~GameEngine() {
	delete map;
	delete neutralPlayer;
	delete deck;
	for (auto p : playersList)
		delete p;
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
	playersList.push_back(new Player(playerName));
}

void GameEngine::addPlayer(Player* p)
{
	playersList.push_back(p);
}

void GameEngine::readMap(string mapName)
{
	MapLoader mapLoader;
	this->map = mapLoader.readMap(mapName);
}

Player* GameEngine::getNeutralPlayer()
{
	if (this->neutralPlayer == nullptr)
		return new Player("Neutral");
	else
		return this->neutralPlayer;
}

bool GameEngine::find_Bool(const vector<bool>& bools, bool b) {
	bool result = false;
	if (find(bools.begin(), bools.end(), b) != bools.end()) {
		result = true;
	}

	return result;

}

void GameEngine::enableTournamentMode() {
	isTournamentMode = true;
}

bool GameEngine::checkTournamentMode()
{
	return isTournamentMode;
}
