#include <string>
#include <iostream>
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
using namespace std;
#include "LoggingObserver.h"


class GameEngine :public ILoggable, public Subject{
private:
	string state;
	string state_start;
	string state_map_loaded;
	string state_map_validated;
	string state_players_added;
	string state_assign_reinforcement;
	string state_issue_orders;
	string state_execute_orders;
	string state_win;
	string state_Terminated;

public:

	GameEngine();
	GameEngine(const GameEngine& copy);
	GameEngine& operator = (const GameEngine& copy);
	string getState();
	void setState(string newState);
	friend ostream& operator << (ostream& out, const GameEngine& gameEngine);
	//define stringToLog method from abstract base class Iloggable
	string stringToLog();
	
};


#endif
