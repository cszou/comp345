#include <string>
#include <iostream>
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
using namespace std;



class GameEngine {
private:
	string* state;
  string* state_start;
  string* state_map_loaded;
  string* state_map_validated;
  string* state_players_added;
  string* state_assign_reinforcement;
	string* state_issue_orders;
	string* state_execute_orders;
	string* state_win;
	string* state_Terminated;


public:

	GameEngine();
	GameEngine(const GameEngine& copy);
	GameEngine& operator = (const GameEngine& copy);
	friend ostream& operator << (ostream& out, const GameEngine& gameEngine);
	void Test();


};


#endif
