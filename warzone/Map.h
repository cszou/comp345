#pragma once
#include <string>
using std::string;
#include <vector>
using std::vector;
class Continent;
class Territory;

class Map {
public:
	Map();
	Map(const Map& m);
	Map& operator =(const Map& m);
	~Map();
	void addTerritory(Territory* t);
	void addContinent(Continent* t);
	void showAllContinents();
	void showAllTerritories();
	bool territoryExists(string $s);
	Territory* getTerritory(string name) const;
	Continent* getContinent(string name) const;
	vector<Territory*>& getAllTerritories();
	int getTerritoryNum() const;
	bool validate();
private:
	vector<Territory*> territories;
	vector<Continent*> continents;
	int totalTerritories;
	void traverse(Territory* t, vector<bool>& v);
};

class Continent {
public:
	Continent();
	Continent(string name, int num);
	Continent(const Continent& c);
	Continent& operator =(Continent& c);
	Territory* getTerritories();
	int getTerritoryNumber();
	string getName() const;
	void addTerritories(Territory* t);
	void showAllTerritories();
	friend std::ostream& operator<<(std::ostream&, const Continent&);
private:
	int numberOfTerritory;
	string continentName;
	vector<Territory*> territoriesList;
	int bonus;
};

class Territory{
public:
	Territory();
	Territory(string name);
	Territory(const Territory& t);
	Territory(string n, int x, int y, Continent* c);
	Territory& operator =(const Territory& t);
	int getNumberOfArmies() const;
	string getOwner() const;
	string getName() const;
	Continent* getContinent() const;
	int getX() const;
	int getY() const;
	void setNumberOfArmies(int numOfArmies);
	void setName(string name);
	void setOwner(string o);
	void setContinent(Continent* c);
	void setX(int x);
	void setY(int y);
	void addNeighbour(Territory* t);
	void showNeighbours();
	vector<Territory*> &getNeighbours();
	friend std::ostream& operator<<(std::ostream&, const Territory&);
private:
	vector<Territory*> neighbours;
	Continent* continent;
	string name;
	string owner;
	int numberOfArmies;
	int coordX;
	int coordY;
};

void loader();
bool validate(const Map* m);

