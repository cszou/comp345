#include "GameEngine.h"
using namespace std;

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

void GameEngine::addPlayer() {
	cout << "Please enter player name: ";
	string name;
	cin >> name;
	playerList.push_back(new Player(name));
}
	
