#include <string>
#include <iostream>
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
using namespace std;
#include "LoggingObserver.h"
#include "Player.h"
#include <vector>
#include "Orders.h"
#include <algorithm>
#include <random>
#include "Utilities.h"
#include "Map.h"
#include <map>
#include <iterator>
using std::vector;
class Deck;

class GameEngine :public ILoggable, public Subject {
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
	Player* neutralPlayer;
	bool isTournamentMode;

public:
	GameEngine();
	GameEngine(const GameEngine& copy);
	~GameEngine();
	GameEngine& operator = (const GameEngine& copy);
	string getState();
	void setState(string newState);
	friend ostream& operator << (ostream& out, const GameEngine& gameEngine);
	//define stringToLog method from abstract base class Iloggable
	string stringToLog();
	void addPlayer(string playerName);
	void addPlayer(Player* p);
	void readMap(string mapName);
	Player* getNeutralPlayer();
	Map* map;
	vector<Player*> playersList;
	Deck* deck;
	bool startupFinished;
	bool find_Territory(const vector<Territory*>& territories, Territory* t);
	bool find_Order_Name(const vector<string>& names, string s);
	bool find_Bool(const vector<bool>& bools, bool b);
	// varibles and methods for tournament mode
	vector<Map*> tournamentMaps;
	void enableTournamentMode();
	bool checkTournamentMode();
	int numOfGame;
	int maxNumberOfTurns;
};


#endif
