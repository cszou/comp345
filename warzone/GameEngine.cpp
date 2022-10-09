#include "GameEngine.h"
using namespace std;

//Constructor
GameEngine::GameEngine() {

	state_start = new string("Start");
	state_map_loaded = new string("Map Loaded");
	state_map_validated = new string("Map Validated");
	state_players_added = new string("Players Added");
	state_assign_reinforcement = new string("Assign Reinforcement");
	state_issue_orders = new string("Issue_Orders");
	state_execute_orders = new string("Execute Orders");
	state_win = new string("Win");
	state_Terminated = new string("Terminated");
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

//Stream insersion operator
 ostream& operator << (ostream& out, const GameEngine& gameEngine) {
	 out << "Game_Engine";
	 return out;

}

 void GameEngine::Test() {

	 string command;
	 bool valid = false;

	 while (*state != "Terminated") {
		 valid = false;
		 cout << "Current State: " << *state <<endl;
		 if (state == state_win) {
			 cout << "The game has ended. Do you want to restart the game? (Yes/No) " << endl;
			 cin >> command;
			 if (command == "Yes") {
				 state = state_start;
			 }
			 else {
				 state = state_Terminated;
			 }
		 }
		 else {
			 cout << "Please enter a valid command " << endl;
			 cin >> command;
			 while (valid == false) {
				 if (state == state_start) {
					 if (command == "Load_Map") {
						 state = state_map_loaded;
						 valid = true;
					 }
					 else {
						 cout << "Invalid Command! Please try again (For example: Load_Map) " << endl;
						 cin >> command;

					 }
				 }
				 else if (state == state_map_loaded) {
					 if (command == "Load_Map") {
						 valid = true;
					 }
					 else if (command == "Validate_Map") {
						 state = state_map_validated;
						 valid = true;
					 }
					 else {
						 cout << "Invalid Command! Please try again (For example: Load_Map / Validate_Map) " << endl;
						 cin >> command;
					 }
				 }
				 else if (state == state_map_validated) {
					 if (command == "Add_Player") {
						 state = state_players_added;
						 valid = true;
					 }
					 
					 else {
						 cout << "Invalid Command! Please try again (For example: Add_Player) " << endl;
						 cin >> command;
					 }
				 }
				 else if (state == state_players_added) {
					 if (command == "Add_Player") {
						 valid = true;
					 }
					 else if (command == "Assign_Countries") {
						 state = state_assign_reinforcement;
						 valid = true;
					 }

					 else {
						 cout << "Invalid Command! Please try again (For example: Add_Player/Assign_Countries ) " << endl;
						 cin >> command;
					 }
				 }
				 else if (state == state_assign_reinforcement) {
					 if (command == "Issue_Order") {
						 state = state_issue_orders;
						 valid = true;
					 }
				
					 else {
						 cout << "Invalid Command! Please try again (For example: Issue_Order ) " << endl;
						 cin >> command;
					 }
				 }
				 else if (state == state_issue_orders) {
					 if (command == "Issue_Order") {
						 valid = true;
					 }
					 else if (command == "End_Issue_Orders") {
						 state = state_execute_orders;
						 valid = true;
					 }

					 else {
						 cout << "Invalid Command! Please try again (For example: Issue_Order/End_Issue_Orders  ) " << endl;
						 cin >> command;
					 }
				 }
				 else if (state == state_execute_orders) {
					 if (command == "Execute_Order") {
						 valid = true;
					 }
					 else if (command == "End_Execute Orders") {
						 state = state_assign_reinforcement;
						 valid = true;
					 }
					 else if (command == "Win") {
						 state = state_win;
						 valid = true;
					 }

					 else {
						 cout << "Invalid Command! Please try again (For example: Execute_Order/ End_Execute_Orders/Win  ) " << endl;
						 cin >> command;
					 }
				 }
				 

			 }

		 }
		
		 





	 }




 }

