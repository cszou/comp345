#pragma once
#include <string>
using std::string;
#include <vector>
using std::vector;
class Continent;
class Territory;
class Player;

// Map class to store the map info
class Map {
public:
	Map(); //default constructor
	Map(const Map& m); //copy constructor
	Map& operator =(const Map& m); //assigment operator
	~Map(); //destructor
	void addTerritory(Territory* t); //add a territory
	void updateTerritory(Territory* t); //update the territory info 
	void addContinent(Continent* t); //add a continent
	void showAllContinents(); //show all continents info
	void showAllTerritories(); //show all territories info
	bool territoryExists(string s); //check if the territory exists by the name, return true if exists
	Territory* getTerritory(string name) const; //get a territory pointer by the name
	Continent* getContinent(string name) const; //get a continent pointer by the name
	int getTerritoryNum() const; //get total territory number
	int getContinentNum() const; //get total continent number
	bool validate(); //validate map
	friend std::ostream& operator<<(std::ostream&, const Map&); //stream insertion
	vector<Territory*> getAllTerritories();
	vector<Continent*> getAllContinents();
	void setName(string name);
	string getName();
private:
	string name; //map name
	vector<Territory*> territories; //vector to store the territories
	vector<Continent*> continents; //vector to store the continents
	int territoryNum; //total number of territories
	int continentNum; //total number of continents
	void traverse(Territory* t, vector<bool>& v); //helper method for DFS traverses
};

// Continent class to store continent info
class Continent {
public:
	Continent(); //default constructor
	Continent(string name, int num); //constructor with name and bonus
	Continent(const Continent& c); //copy constructor
	Continent& operator =(Continent& c); //assignment operator
	int getTerritoryNumber() const; //get total number of territories
	string getName() const; //get continent name
	void addTerritories(Territory* t); //add a territory to a continent
	void showAllTerritories(); //show info of all territories in this continent
	vector<Territory*> getTerritories(); //get territories
	bool validate(); //validate the continent in connected
	int getBonus();
	bool ownedBy(Player* p);
	friend std::ostream& operator<<(std::ostream&, const Continent&); //stream insertion
private:
	int numberOfTerritory; //total number of territories
	int bonus; //bonus if all territories are controlled by one player
	string continentName; //name
	vector<Territory*> territoriesList; //vactor to store the territories
	void traverse(Territory* t, vector<bool>& v); //helper method for DFS traverses
	bool inContinent(Territory* t); //helper method to check if the territory is in the continent, return true if in
};

// Territory class to store country info
class Territory{
public:
	Territory(); //default constructor
	Territory(string name); //constructor with name only
	Territory(const Territory& t); //copy constructor
	Territory(string n, int x, int y, Continent* c); //constructor with name, coordinates and continent info
	Territory& operator =(const Territory& t); //assignment operator
	int getNumberOfArmies() const; //get number of armies on the territory
	Player* getOwner() const; //get owner
	string getName() const; //get name of the territory
	Continent* getContinent() const; //get a pointer of the continent
	int getX() const; //get X coordinate
	int getY() const; //get Y coordinate
	void setNumberOfArmies(int numOfArmies); //set army number
	void setName(string name); //set name
	void setOwner(Player* p); //set owner
	void setContinent(Continent* c); //set continent in which the territory is located
	void setX(int x); //set X coordinate
	void setY(int y); //set Y coordinate
	void addNeighbour(Territory* t); //add a connected neighbour
	bool checkNeighbours(Territory* k) ;
	void showNeighbours(); //show all neighbours
	vector<Territory*> getNeighbours(); //get the neighbours
	friend std::ostream& operator<<(std::ostream&, const Territory&); //stream insertion
private:
	vector<Territory*> neighbours; //a vector to store all the neighbours
	Continent* continent; //continet it belongs to
	string name; //territory name
	Player* owner; //owner of the territory
	int numberOfArmies; //total number of armies
	int coordX; //X coordinate
	int coordY; //Y coordinate
};

//MapLoader class to load the map
class MapLoader {
public:
	static Map* readMap(string mapPath); //read map file and return a pointer to the loaded map
private:
	static Map* map;
};
