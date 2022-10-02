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
#include <vector>
using std::vector;
#include <sstream>
using std::stringstream;
#include <algorithm>
using std::find;

Map::Map() {
	this->totalTerritories = 0;
}

Map::Map(const Map& m)
{
	this->totalTerritories = m.totalTerritories;
}

Map& Map::operator=(const Map& m)
{
	this->totalTerritories = m.totalTerritories;
	return *this;
}

Map::~Map()
{
	for (auto& t : territories)
		delete t;
	for (auto& c : continents)
		delete c;
}

void Map::addTerritory(Territory* t) {
	if (!territoryExists(t->getName()))
	{
		this->territories.push_back(t);
		this->totalTerritories++;
	}
	else
	{
		this->getTerritory(t->getName())->setX(t->getX());
		this->getTerritory(t->getName())->setY(t->getY());
		this->getTerritory(t->getName())->setContinent(t->getContinent());
	}
	if (t->getContinent() != nullptr)
		for (auto& c : continents) {
			if (t->getContinent()->getName() == c->getName())
			{
				c->addTerritories(t);
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
	cout << "Total " << this->totalTerritories << " territories." << endl;
}

void Map::showAllTerritories() {
	cout << "**********Showing all territories**********" << endl;
	for (const auto& t : territories)
		cout << *t << endl;
}

bool Map::territoryExists(string s) {
	for (auto $t : territories)
		if (($t)->getName() == s)
			return true;
	return false;
}

Territory* Map::getTerritory(string name) const
{
	for (auto& t : territories)
		if (t->getName() == name)
			return t;
}

Continent* Map::getContinent(string name) const
{
	for (auto& c : continents)
		if (c->getName() == name)
			return c;
}

vector<Territory*> Map::getAllTerritories() const
{
	return territories;
}

Territory::Territory(string name)
{
	this->name = name;
	this->coordX = -1;
	this->coordY = -1;
	this->continent = nullptr;
	this->owner = "";
	this->numberOfArmies = 0;
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

Territory::Territory(string n, int x, int y, Continent* c) {
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

void Territory::setContinent(Continent* c)
{
	this->continent = c;
}

void Territory::setX(int x)
{
	this->coordX = x;
}

void Territory::setY(int y)
{
	this->coordY = y;
}

void Territory::addNeighbour(Territory* t)
{
	this->neighbours.push_back(t);
}

void Territory::showNeighbours()
{
	for (auto& t : neighbours)
		cout << t->getName() << ", ";
	cout << endl;
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

Continent* Territory::getContinent() const
{
	return this->continent;
}

int Territory::getX() const
{
	return coordX;
}

int Territory::getY() const
{
	return coordY;
}

void Territory::setName(string name) {
	this->name = name;
}

string Territory::getName() const {
	return this->name;
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

string Continent::getName() const
{
	return continentName;
}

void Continent::addTerritories(Territory* t) {
	this->territoriesList.push_back(t);
}

void Continent::showAllTerritories() {
	cout << this->getName() << " has " << this->territoriesList.size() << " territories: " << endl;
	for (const auto& t : territoriesList) {
		cout << *t;
		cout << " It has neighbours: ";
		t->showNeighbours();
	}
	cout << endl;
}

std::ostream& operator<<(std::ostream& strm, const Continent& c)
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
	string q = "y";
	ifstream mapReader;
	while (q == "y")
	{
		cout << "Please emter the map name: ";
		cin >> path;
		mapReader.open(path);
		if (!mapReader.is_open()) {
			cout << "failed to open " << path << endl;
			cout << "Do you want to try again? (y/n)" << endl;
			cin >> q;
		}
		else
			q = "n";
	}
	if (!mapReader.is_open()) {
		cout << "Program ended" << endl;
		exit(0);
	}
	while (!mapReader.eof()) {
		getline(mapReader, line, '\n');
		if (line == "[Continents]") {
			s = "=";
			name = "";
			int num = 0;
			while (line == "" || line == "[Continents]")
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
			while (!mapReader.eof()) {
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
				Territory* t = new Territory(tInfo[0], stoi(tInfo[1], nullptr), stoi(tInfo[2], nullptr), gameMap.getContinent(tInfo[3]));
				gameMap.addTerritory(t);
				for (int i = 4; i < tInfo.size(); i++) {
					if (gameMap.territoryExists(tInfo[i]))
					{
						t->addNeighbour(gameMap.getTerritory(tInfo[i]));
					}
					else
					{
						Territory* newTerritory = new Territory(tInfo[i]);
						gameMap.addTerritory(newTerritory);
						t->addNeighbour(newTerritory);
					}
				}
			}
		}
	}
	mapReader.close();
	cout << "All loaded." << endl;
	gameMap.showAllContinents();
	cout << endl << "******************Validating map******************" << endl;
	if (validate(&gameMap))
		cout << "This is a valid map." << endl;
	else
		cout << "The map is invalid." << endl;
}

bool validate(const Map* m)
{
	// validate each country is belong to one and only one continent
	for (auto& t : m->getAllTerritories())
		if (t->getContinent() == nullptr)
			return false;
	return true;
}