#include "MapDriver.h"
#include "Map.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

//load the map and make sure a valid map is loaded.
void testLoadMaps() {
	cout << "Part 1: Map" << endl;
	Map* gameMap = nullptr;
	string ans = "y";
	while(ans == "y")
	{
		cout << "Please enter the map name: ";
		string path;
		cin >> path;
		Map* gameMap = MapLoader::readMap(path);
		while (gameMap == nullptr) {
			cout << "No map is loaded. Please try again: ";
			cin >> path;
			gameMap = MapLoader::readMap(path);
		}
		if (gameMap->validate())
			cout << "This is a valid map.\n";
		else
			cout << "This is not a valid map.\n";
		gameMap->showAllContinents();
		cout << "Do you want try again (y/n): ";
		cin >> ans;
	}
	delete gameMap;
	gameMap = nullptr;
	cout << "Map demo end." << endl << endl;
}