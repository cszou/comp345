#include "GameEngineDriver.h"
#include "GameEngine.h"
#include <iostream>
using std::cin;
using std::cout;
#include <string>
using std::string;


void testGameStates() {

	string command;
	bool valid = false;
	GameEngine* engine = new GameEngine();

	while (engine->getState() != "Terminated") {
		valid = false;
		cout << "Current State: " << engine->getState() << endl;
		if (engine->getState() == "Win") {
			cout << "The game has ended. Do you want to restart the game? (Yes/No) " << endl;
			cin >> command;
			if (command == "Yes") {
				engine->setState("Start");
			}
			else {
				engine->setState("Terminated");
			}
		}
		else {
			cout << "Please enter a valid command " << endl;
			cin >> command;
			while (valid == false) {
				if (engine->getState() == "Start") {
					if (command == "Load_Map") {
						engine->setState("Map Loaded");
						valid = true;
					}
					else {
						cout << "Invalid Command! Please try again (For example: Load_Map) " << endl;
						cin >> command;
					}
				}
				else if (engine->getState() == "Map Loaded") {
					if (command == "Load_Map") {
						valid = true;
					}
					else if (command == "Validate_Map") {
						engine->setState("Map Validated");
						valid = true;
					}
					else {
						cout << "Invalid Command! Please try again (For example: Load_Map / Validate_Map) " << endl;
						cin >> command;
					}
				}
				else if (engine->getState() == "Map Validated") {
					if (command == "Add_Player") {
						engine->setState("Players Added");
						valid = true;
					}

					else {
						cout << "Invalid Command! Please try again (For example: Add_Player) " << endl;
						cin >> command;
					}
				}
				else if (engine->getState() == "Players Added") {
					if (command == "Add_Player") {
						valid = true;
					}
					else if (command == "Assign_Countries") {
						engine->setState("Assign Reinforcement");
						valid = true;
					}

					else {
						cout << "Invalid Command! Please try again (For example: Add_Player/Assign_Countries ) " << endl;
						cin >> command;
					}
				}
				else if (engine->getState() == "Assign Reinforcement") {
					if (command == "Issue_Order") {
						engine->setState("Issue_Orders");
						valid = true;
					}

					else {
						cout << "Invalid Command! Please try again (For example: Issue_Order ) " << endl;
						cin >> command;
					}
				}
				else if (engine->getState() == "Issue_Orders") {
					if (command == "Issue_Order") {
						valid = true;
					}
					else if (command == "End_Issue_Orders") {
						engine->setState("Execute Orders");
						valid = true;
					}

					else {
						cout << "Invalid Command! Please try again (For example: Issue_Order/End_Issue_Orders  ) " << endl;
						cin >> command;
					}
				}
				else if (engine->getState() == "Execute Orders") {
					if (command == "Execute_Order") {
						valid = true;
					}
					else if (command == "End_Execute Orders") {
						engine->setState("Assign Reinforcement");
						valid = true;
					}
					else if (command == "Win")
						engine->setState("Win");
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