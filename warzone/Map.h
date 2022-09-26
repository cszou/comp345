#pragma once
#include <list>
using std::list;
#include <string>
using std::string;


class Territory {
public:
	Territory() {};
	Territory(const Territory& t);
	Territory(string n, int x, int y, string c);
	Territory& operator =(const Territory& t);
	void setOwner(string o);
	string getOwner() const;
	void setNumberOfArmies(int numOfArmies);
	int getNumberOfArmies() const;
	string getContinent() const;
	friend std::ostream& operator<<(std::ostream&, const Territory&);
private:
	string name;
	string owner;
	string continent;
	int numberOfArmies;
	int coordX;
	int coordY;
};

class Continent {
public:
	Continent() {};
	Continent(string name, int num);
	Continent(const Continent& c);
	Continent& operator =(Continent& c);
	Territory* getTerritories();
	int getTerritoryNumber();
	string getName();
	void addTerritories(Territory* t);
	void showAllTerritories();
	friend std::ostream& operator<<(std::ostream&, const Continent&);
private:
	int numberOfTerritory;
	string continentName;
	list<Territory*> tList;
	int bonus;
};

class Map {
public:
	Map() {};
	Map(const Map& m);
	Map& operator =(const Map& m);
	void addTerritory(Territory* t);
	void addContinent(Continent* t);
	void showAllContinents();
	void showAllTerritories();
private:
	bool validate();
	list<Territory*> territories;
	list<Continent*> continents;
	int totalTerritories;
};

void loader();

