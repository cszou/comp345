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
		//cout << t->getName() << " (" << t << ") " << "added" << endl;
	}
	else
	{
		//cout << "Update " << t->getName() << endl;
		this->getTerritory(t->getName())->setX(t->getX());
		this->getTerritory(t->getName())->setY(t->getY());
		this->getTerritory(t->getName())->setContinent(t->getContinent());
	}
	if (t->getContinent() != nullptr)
		for (auto& c : continents) {
			if (t->getContinent()->getName() == c->getName())
			{
				c->addTerritories(this->getTerritory(t->getName()));
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
	{
		cout << *t << endl;
		cout << "Neighbours: ";
		for (auto n : t->getNeighbours())
			cout << n->getName() << ", ";
		cout << endl;
	}
}

bool Map::territoryExists(string s) {
	//cout << s << endl;
	//cout << "checking: " << s << endl;
	//cout << "we have: ";
	for (auto& t : territories)
	{
		//cout << t->getName() << ", ";
		if (t->getName() == s)
		{
			//cout << endl;
			return true;
		}
	}
	//cout << endl;
	return false;
}

Territory* Map::getTerritory(string name) const
{
	for (auto& t : territories)
		if (t->getName() == name)
			return t;
	return nullptr;
}

Continent* Map::getContinent(string name) const
{
	for (auto& c : continents)
		if (c->getName() == name)
			return c;
	return nullptr;
}

vector<Territory*>& Map::getAllTerritories()
{
	return this->territories;
}

int Map::getTerritoryNum() const {
	return this->totalTerritories;
}

bool Map::validate()
{
	// validate each country is belong to one and only one continent
	for (auto& t : territories)
		if (t->getContinent() == nullptr)
			return false;
	// validate map is connected
	vector<bool> visited;
	for (int i = 0; i < totalTerritories; i++)
		visited.push_back(false);
	for (auto& t : territories) {
		for (int i = 0; i < totalTerritories; i++)
			visited[i] = false;
		traverse(t, visited);
		/*for (bool v : visited)
			cout << v << ",";*/
			//cout << endl;
		for (int i = 0; i < totalTerritories;i++)
			if (!visited[i])
			{
				//cout << i << endl;
				return false;
			}
	}
	// validate continent is connected;

	return true;
}

void Map::traverse(Territory* t, vector<bool>& v) {
	//cout << "checking: " << t->getName();
	//cout << "with " << t->getNeighbours().size() << " neighbours." << endl;
	auto it = find(territories.begin(), territories.end(), t);
	v[it - territories.begin()] = true;
	/*for (auto& tNeighbour : t->getNeighbours()) {
		cout << tNeighbour->getName() << ", ";
	}*/
	//cout << endl;
	for (auto& tNeighbour : t->getNeighbours()) {
		//cout << tNeighbour->getName() << endl;
		auto it2 = find(territories.begin(), territories.end(), tNeighbour);
		if (!v[it2 - territories.begin()])
			traverse(tNeighbour, v);
	}
}

Territory::Territory() {
	this->name = "";
	this->coordX = -1;
	this->coordY = -1;
	this->continent = nullptr;
	this->owner = "";
	this->numberOfArmies = 0;
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
	for (auto t : neighbours)
		cout << t->getName() << ", ";
	//cout << t << ", ";
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

vector<Territory*>& Territory::getNeighbours() {
	return this->neighbours;
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

Continent::Continent() {
	this->numberOfTerritory = 0;
	this->continentName = "";
	this->bonus = 0;
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
	//return strm << "Territory name: " << t.name << " (" << &t << ") " " at coordinate: (" << t.coordX << ", " << t.coordY << ") in continent " << (t.continent)->getName() << ".";
	return strm << "Territory name: " << t.name << " at coordinate: (" << t.coordX << ", " << t.coordY << ") in continent " << (t.continent)->getName() << ".";
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
				//cout << t->getName() << " (" << t << ") 0" << endl;
				//cout << "try adding :" << t->getName() << " (" << t << ")" << endl;
				gameMap.addTerritory(t);
				//for (auto t : gameMap.getAllTerritories()) {
					//cout << t << endl;
				//}
				for (int i = 4; i < tInfo.size(); i++) {
					if (gameMap.territoryExists(tInfo[i]))
					{
						//cout << "we all ready have " << tInfo[i] << endl;
						//cout << gameMap.getTerritory(t->getName()) << endl;
						//cout << gameMap.getTerritory(t->getName())->getName() << endl;
						//cout << t << endl;
						//cout << t->getName() << endl;
						//cout << gameMap.getTerritory(tInfo[i]) << endl;
						gameMap.getTerritory(t->getName())->addNeighbour(gameMap.getTerritory(tInfo[i]));
					}
					else
					{
						//cout << tInfo[i] << " does not exist." << endl;
						Territory* newTerritory = new Territory(tInfo[i]);
						gameMap.addTerritory(newTerritory);
						gameMap.getTerritory(t->getName())->addNeighbour(newTerritory);
					}
				}
			}
		}
	}
	mapReader.close();
	cout << "All loaded." << endl;
	gameMap.showAllContinents();
	//for (int i = 0;i < 4;i++)
	//	cout << i << ": " << gameMap.getAllTerritories()[i]->getName() << " ,address: " << gameMap.getAllTerritories()[i] << endl;
	//for (auto t : gameMap.getAllTerritories()) {
	//	cout << t->getName() << " ,address: " << t << endl;
	//	for (auto nt : t->getNeighbours()) {
	//		cout << "\t" << nt->getName() << " ,address: " << nt << endl;
	//	}
	//}
	cout << endl << "******************Validating map******************" << endl;
	if (gameMap.validate())
		cout << "This is a valid map." << endl;
	else
		cout << "The map is invalid." << endl;
}