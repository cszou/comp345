#include "Map.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <fstream>
using std::ifstream;
using std::getline;
#include <string>
using std::string;
#include <list>
using std::list;
#include <vector>
using std::vector;
#include <sstream>
using std::stringstream;
#include <algorithm>
using std::find;

Map::Map(const Map& m)
{
	this->totalTerritories = m.totalTerritories;
	//this->t = m.t;
}

bool Map::validate()
{
	return true;
}

Map& Map::operator=(const Map& m)
{
	this->totalTerritories = m.totalTerritories;
	//this->t = m.t;
	return *this;
}

void Map::addTerritory(Territory* t) {
	this->territories.push_back(t);
	list<Continent*>::iterator it;
	for (it = this->continents.begin(); it != this->continents.end(); it++) {
		if (t->getContinent() == (*it)->getName())
		{
			(*it)->addTerritories(t);
			break;
		}
	}
}

void Map::addContinent(Continent* c) {
	this->continents.push_back(c);
}

void Map::showAllContinents() {
	cout << "**********Showing all continents*********" << endl;
	for (const auto& c : continents)
	{
		cout << *c << endl;
		c->showAllTerritories();
	}
}

void Map::showAllTerritories() {
	cout << "**********Showing all territories**********" << endl;
	for (const auto& t : territories)
		cout << *t << endl;
}

Territory::Territory(const Territory& t)
{
	this->name = t.name;
	this->coordX = t.coordX;
	this->coordY = t.coordY;
	this->continent = t.continent;
	this->owner = t.owner;
	this->numberOfArmies = t.numberOfArmies;
}

Territory::Territory(string n, int x, int y, string c) {
	this->name = n;
	this->coordX = x;
	this->coordY = y;
	this->continent = c;
	this->owner = "";
	this->numberOfArmies = 0;
}

Territory& Territory::operator=(const Territory& t)
{
	this->numberOfArmies = t.numberOfArmies;
	this->coordX = t.coordX;
	this->coordY = t.coordY;
	this->owner = t.owner;
	this->continent = t.continent;
	return *this;
}

void Territory::setOwner(string o)
{
	this->owner = o;
}

string Territory::getOwner() const
{
	return this->owner;
}

void Territory::setNumberOfArmies(int numOfArmies)
{
	this->numberOfArmies = numOfArmies;
}

int Territory::getNumberOfArmies() const
{
	return this->numberOfArmies;
}

string Territory::getContinent() const
{
	return this->continent;
}

Continent::Continent(string name, int num) {
	this->bonus = num;
	this->continentName = name;
}

Continent::Continent(const Continent& c)
{
	this->numberOfTerritory = c.numberOfTerritory;
	this->continentName = c.continentName;
}

Continent& Continent::operator=(Continent& c)
{
	this->numberOfTerritory = c.numberOfTerritory;
	this->continentName = c.continentName;
	return *this;
}

Territory* Continent::getTerritories()
{
	return nullptr;
}

int Continent::getTerritoryNumber()
{
	return numberOfTerritory;
}

string Continent::getName()
{
	return continentName;
}

void Continent::addTerritories(Territory* t) {
	this->tList.push_back(t);
}

void Continent::showAllTerritories() {
	cout << this->getName() << " has " << this->tList.size() << " territories: " << endl;
	for (const auto& t : tList) {
		cout << *t << endl;
	}
	cout << endl;
}

std::ostream& operator<<(std::ostream &strm, const Continent &c)
{
	return strm << "Continent: " << c.continentName << " ,bonus: " << c.bonus;
}

std::ostream& operator<<(std::ostream& strm, const Territory& t)
{
	return strm << "Territory name: " << t.name << " at coordinate: (" << t.coordX << ", " << t.coordY << ") at continent " << t.continent << ".";
}

void loader()
{
	Map gameMap;
	string line;
	string path;
	string s;
	string name;
	cout << "Please emter the map name: ";
	cin >> path;
	ifstream mapReader(path);
	if (!mapReader.is_open()) {
		cout << "failed to open " << path << endl;
	}
	while (!mapReader.eof()) {
		getline(mapReader, line, '\n');
		if (line == "[Continents]") {
			s = "=";
			name = "";
			int num = 0;
			while(line == "" || line == "[Continents]")
				getline(mapReader, line, '\n');
			while (line != "") {
				int len = line.length();
				string::size_type pos = line.find(s);
				name = line.substr(0, pos);
				num = stoi(line.substr(pos + 1, len - pos), nullptr);
				Continent* c = new Continent(name, num);
				gameMap.addContinent(c);
				getline(mapReader, line, '\n');
			}
			cout << endl;
		}
		else if (line == "[Territories]") {
			s = ",";
			name = "";
			while (!mapReader.eof()){
				getline(mapReader, line, '\n');
				if (line == "")
					continue;
				vector<string> tInfo;
				int start = 0;
				int end = 0;
				int len = line.length();
				string d = ",";
				while (end >= 0) {
					end = line.find(d);
					tInfo.push_back(line.substr(start, end));
					line = line.substr(end + 1, len - end + 1);
				}
				Territory *t = new Territory(tInfo[0], stoi(tInfo[1], nullptr), stoi(tInfo[2], nullptr), tInfo[3]);
				gameMap.addTerritory(t);
			}
		}
	}
	mapReader.close();
	cout << "All loaded." << endl;
	gameMap.showAllContinents();
	//gameMap.showAllTerritories();
}
