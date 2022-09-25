#pragma once
#include <list>
using std::list;
#include <string>
using std::string;


class Territory {
public:
	Territory() {};
	Territory(const Territory& t);
	Territory& operator =(const Territory& t);
	void setOwner(string o);
	string getOwner() const;
	void setNumberOfArmies(int numOfArmies);
	int getNumberOfArmies() const;
private:
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
	friend std::ostream& operator<<(std::ostream&, const Continent&);
private:
	int numberOfTerritory;
	string continentName;
	list<Territory*> tList;
};

class Map {
public:
	Map() {};
	Map(const Map& m);
	Map& operator =(const Map& m);
private:
	bool validate();
	list<Territory*> territories;
	int totalTerritories;
};

void loader();

