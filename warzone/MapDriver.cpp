#include "MapDriver.h"
#include "Map.h"
#include <iostream>
using std::cout;
using std::endl;

//load the map and make sure a valid map is loaded.
void testLoadMaps() {
	cout << "Part 1: Map" << endl;
	Map* gameMap = MapLoader::readMap();
	while (gameMap == nullptr) {
		cout << "No map is loaded. Please try again." << endl;
		gameMap = MapLoader::readMap();
	}
	delete gameMap;
	cout << "Map demo end." << endl << endl;
}