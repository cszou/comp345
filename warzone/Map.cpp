#include "Map.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <fstream>
using std::getline;
using std::ifstream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <sstream>
using std::stringstream;
#include <algorithm>
using std::find;
using std::replace;
#include "Player.h"

// default constructor
Map::Map()
{
	this->territoryNum = 0;
	this->continentNum = 0;
}

// copy constructor
Map::Map(const Map &m)
{
	this->territoryNum = m.territoryNum;
	this->continentNum = m.territoryNum;
	for (auto c : m.continents)
		this->continents.push_back(new Continent(*c));
	for (auto t : m.territories)
		this->territories.push_back(new Territory(*t));
}

// assigment operator
Map &Map::operator=(const Map &m)
{
	this->territoryNum = m.territoryNum;
	this->continentNum = m.territoryNum;
	for (auto c : m.continents)
		this->continents.push_back(new Continent(*c));
	for (auto t : m.territories)
		this->territories.push_back(new Territory(*t));
	return *this;
}

// destructor, delete each territory and continent
Map::~Map()
{
	for (auto &t : territories)
		delete t;
	for (auto &c : continents)
		delete c;
}

// add a territory, if the territory contains continent info also all add it to the continent
void Map::addTerritory(Territory *t)
{
	this->territories.push_back(t);
	this->territoryNum++;
	if (t->getContinent() != nullptr)
		for (auto &c : continents)
		{
			if (t->getContinent()->getName() == c->getName())
			{
				c->addTerritories(this->getTerritory(t->getName()));
				break;
			}
		}
}

// update a territory info with coordinates, name, continent
void Map::updateTerritory(Territory *t)
{
	this->getTerritory(t->getName())->setX(t->getX());
	this->getTerritory(t->getName())->setY(t->getY());
	this->getTerritory(t->getName())->setContinent(t->getContinent());
	if (t->getContinent() != nullptr)
		for (auto &c : continents)
		{
			if (t->getContinent()->getName() == c->getName())
			{
				c->addTerritories(this->getTerritory(t->getName()));
				break;
			}
		}
}

// add a continent
void Map::addContinent(Continent *c)
{
	this->continentNum++;
	this->continents.push_back(c);
}

// show all continents info
void Map::showAllContinents()
{
	cout << *this << endl;
	cout << "**********Showing all continents and territories*********" << endl;
	for (const auto &c : continents)
	{
		cout << *c << endl;
		c->showAllTerritories();
	}
	cout << "Total " << this->territoryNum << " territories." << endl;
}

// show all territories info
void Map::showAllTerritories()
{
	cout << "**********Showing all territories**********" << endl;
	for (const auto &t : territories)
	{
		cout << *t << endl;
		cout << "Neighbours: ";
		for (auto n : t->getNeighbours())
			cout << n->getName() << " ";
		cout << endl;
	}
}

// check if the territory exists by the name, return true if exists
bool Map::territoryExists(string s)
{
	for (auto &t : territories)
		if (t->getName() == s)
			return true;
	return false;
}

// get a territory pointer by the name, return null pointer if not exists
Territory *Map::getTerritory(string name) const
{
	for (auto &t : territories)
		if (t->getName() == name)
			return t;
	return nullptr;
}

// get a continent pointer by the name, return null pointer if not exists
Continent *Map::getContinent(string name) const
{
	for (auto &c : continents)
		if (c->getName() == name)
			return c;
	return nullptr;
}

// get total territory number
int Map::getTerritoryNum() const
{
	return this->territoryNum;
}

// get total continent number
int Map::getContinentNum() const
{
	return continentNum;
}

/*validate the name
  1. each country is belong to one and only one continent
  2. map is connected
  3. validate continent is connected
  DFS algorithm is used
*/
bool Map::validate()
{
	// validate each country is belong to one and only one continent
	for (auto &t : territories)
		if (t->getContinent() == nullptr)
			return false;
	//cout << "unique continent validated" << endl;
	// validate map is connected
	vector<bool> visited;
	for (int i = 0; i < territoryNum; i++)
		visited.push_back(false);
	for (auto &t : territories)
	{
		for (int i = 0; i < territoryNum; i++)
			visited[i] = false;
		traverse(t, visited);
		for (int i = 0; i < territoryNum; i++)
			if (!visited[i])
				return false;
	}
	//cout << "whole map connectivity validated" << endl;
	// validate continent is connected, using DFS and skipping the territory not in the continent
	for (auto c : continents)
		if (!(c->validate()))
			return false;
	//cout << "continent connectivity validated" << endl;
	return true;
}

// helper method for DFS traverses
void Map::traverse(Territory *t, vector<bool> &v)
{
	auto it = find(territories.begin(), territories.end(), t);
	v[it - territories.begin()] = true;
	for (auto &tNeighbour : t->getNeighbours())
	{
		auto it2 = find(territories.begin(), territories.end(), tNeighbour);
		if (!v[it2 - territories.begin()])
			traverse(tNeighbour, v);
	}
}

vector<Territory *> Map::getAllTerritories()
{
	return this->territories;
}

vector<Continent *> Map::getAllContinents()
{
	return this->continents;
}

void Map::setName(string name)
{
	this->name = name;
}

string Map::getName()
{
	return this->name;
}

// default constructor
Continent::Continent()
{
	this->numberOfTerritory = 0;
	this->continentName = "";
	this->bonus = 0;
}

// constructor with name and bonus
Continent::Continent(string name, int num)
{
	// replace(name.begin(), name.end(), ' ', '_');
	this->bonus = num;
	this->continentName = name;
}

// copy constructor
Continent::Continent(const Continent &c)
{
	this->numberOfTerritory = c.numberOfTerritory;
	this->continentName = c.continentName;
	this->bonus = c.bonus;
	for (auto t : territoriesList)
		this->territoriesList.push_back(new Territory(*t));
}

// assignment operator
Continent &Continent::operator=(Continent &c)
{
	this->numberOfTerritory = c.numberOfTerritory;
	this->continentName = c.continentName;
	this->bonus = c.bonus;
	for (auto t : territoriesList)
		this->territoriesList.push_back(new Territory(*t));
	return *this;
}

int Continent::getBonus()
{
	return this->bonus;
}
bool Continent::ownedBy(Player* p)
{
	for (auto t : this->territoriesList)
		if (t->getOwner() != p)
			return false;
	return true;
}
//get total number of territories
int Continent::getTerritoryNumber() const
{
	return numberOfTerritory;
}

// get continent name
string Continent::getName() const
{
	return continentName;
}

// add a territory to a continent
void Continent::addTerritories(Territory *t)
{
	this->territoriesList.push_back(t);
	numberOfTerritory++;
}

// show info of all territories in this continent
void Continent::showAllTerritories()
{
	cout << this->getName() << " has " << this->territoriesList.size() << " territories: " << endl;
	for (const auto &t : territoriesList)
	{
		cout << *t;
		cout << " It has neighbours: ";
		t->showNeighbours();
	}
	cout << endl;
}

// get territories
vector<Territory *> Continent::getTerritories()
{
	return this->territoriesList;
}

/*validate the continent in connected,
 * using DFSand skipping the neighbour not in the same continent
 */
bool Continent::validate()
{
	vector<bool> visited;
	for (int i = 0; i < numberOfTerritory; i++)
		visited.push_back(false);
	for (auto t : territoriesList)
	{
		for (int i = 0; i < numberOfTerritory; i++)
			visited[i] = false;
		traverse(t, visited);
	}
	for (int i = 0; i < numberOfTerritory; i++)
		if (!visited[i])
			return false;
	return true;
}

// helper method for DFS traverses
void Continent::traverse(Territory *t, vector<bool> &v)
{
	auto it = find(territoriesList.begin(), territoriesList.end(), t);
	v[it - territoriesList.begin()] = true;
	for (auto &tNeighbour : t->getNeighbours())
	{
		if (!inContinent(tNeighbour))
			continue;
		auto it2 = find(territoriesList.begin(), territoriesList.end(), tNeighbour);
		if (!v[it2 - territoriesList.begin()])
			traverse(tNeighbour, v);
	}
}

/*helper method
 * to check if the territory is in the continent,
 * return true if in
 */
bool Continent::inContinent(Territory *t)
{
	for (auto territory : territoriesList)
		if (t == territory)
			return true;
	return false;
}

// default constructor
Territory::Territory()
{
	this->name = "";
	this->coordX = -1;
	this->coordY = -1;
	this->continent = nullptr;
	this->owner = nullptr;
	this->numberOfArmies = 0;
}

// constructor with name only
Territory::Territory(string name)
{
	// replace(name.begin(), name.end(), ' ', '_');
	this->name = name;
	this->coordX = -1;
	this->coordY = -1;
	this->continent = nullptr;
	this->owner = nullptr;
	this->numberOfArmies = 0;
}

// copy constructor
Territory::Territory(const Territory &t)
{
	this->name = t.name;
	this->coordX = t.coordX;
	this->coordY = t.coordY;
	if (t.continent != nullptr)
		this->continent = new Continent(*t.continent);
	else
		this->continent = nullptr;
	if (t.owner != nullptr)
		this->owner = new Player(*t.owner);
	else
		this->owner = nullptr;
	this->numberOfArmies = t.numberOfArmies;
}

// constructor with name, coordinates and continent info
Territory::Territory(string n, int x, int y, Continent *c)
{

	// replace(n.begin(), n.end(), ' ', '_');
	this->name = n;
	this->coordX = x;
	this->coordY = y;
	this->continent = c;
	this->owner = nullptr;
	this->numberOfArmies = 0;
}

// assignment operator
Territory &Territory::operator=(const Territory &t)
{
	this->numberOfArmies = t.numberOfArmies;
	this->coordX = t.coordX;
	this->coordY = t.coordY;
	if (t.continent != nullptr)
		this->continent = new Continent(*t.continent);
	else
		this->continent = nullptr;
	if (t.owner != nullptr)
		this->owner = new Player(*t.owner);
	else
		this->owner = nullptr;
	return *this;
}

// get number of armies on the territory
int Territory::getNumberOfArmies() const
{
	return this->numberOfArmies;
}

// get owner
Player *Territory::getOwner() const
{
	return this->owner;
}

// get name of the territory
string Territory::getName() const
{
	return this->name;
}

// get a pointer of the continent
Continent *Territory::getContinent() const
{
	return this->continent;
}

// get X coordinate
int Territory::getX() const
{
	return coordX;
}

// get Y coordinate
int Territory::getY() const
{
	return coordY;
}

// set army number
void Territory::setNumberOfArmies(int numOfArmies)
{
	this->numberOfArmies = numOfArmies;
}

// set neme
void Territory::setName(string name)
{
	this->name = name;
}

void Territory::setOwner(Player *p)
{
	if (getOwner() != p)
	{
		owner = p;
	}
}

// set continent in which the territory is located
void Territory::setContinent(Continent *c)
{
	this->continent = c;
}

// set X coordinate
void Territory::setX(int x)
{
	this->coordX = x;
}

// set Y coordinate
void Territory::setY(int y)
{
	this->coordY = y;
}

// add a connected neighbour
void Territory::addNeighbour(Territory *t)
{
	if (!this->checkNeighbours(t))
	{
		this->neighbours.push_back(t);
		t->addNeighbour(this);
	}
}
// show all neighbours
void Territory::showNeighbours()
{
	for (auto it = neighbours.begin(); it != neighbours.end(); it++)
		if (next(it) != neighbours.end())
			cout << neighbours[it - neighbours.begin()]->getName() << ", ";
		else
			cout << neighbours[it - neighbours.begin()]->getName() << ".";
	cout << endl;
}

// get the neighbours
vector<Territory *> Territory::getNeighbours()
{
	return this->neighbours;
}
bool Territory::checkNeighbours(Territory *k)
{
	for (auto t : getNeighbours())
	{
		if (t == k)
		{
			return true;
		}
	}
	return false;
}

// stream insertion for Map object
std::ostream &operator<<(std::ostream &strm, const Map &m)
{
	return strm << "This map contains " << m.continentNum << " continents with total " << m.territoryNum << " territories.";
}

// stream insertion for Continent object
std::ostream &operator<<(std::ostream &strm, const Continent &c)
{
	return strm << "Continent: " << c.continentName << " ,bonus: " << c.bonus;
}

// stream insertion for Territory object
std::ostream &operator<<(std::ostream &strm, const Territory &t)
{
	if (t.getContinent() == nullptr)
		return strm << "Territory name: " << t.name;
	else
		return strm << "Territory name: " << t.name << " at coordinate: (" << t.coordX << ", " << t.coordY << ") in continent " << (t.continent)->getName() << ".";
}

/* read a file and load map info as gameMap
 * can read any file
 * return a pointer to the loaded map
 */
Map *MapLoader::readMap(string mapPath)
{
	Map *gameMap = new Map();
	string line;
	string s;
	string name;
	string q = "y";
	ifstream mapReader;
	mapReader.open(mapPath);
	// get the file name and open the file for read
	if (!mapReader.is_open())
		while (q == "y")
		{
			cout << "Error. Please enter the map name: ";
			cin >> mapPath;
			mapReader.open(mapPath);
			if (!mapReader.is_open())
			{
				cout << "failed to open " << mapPath << endl;
				cout << "Do you want to try again? (y/n) ";
				cin >> q;
			}
			else
				q = "n";
		}
	if (!mapReader.is_open())
	{
		cout << "Program ended" << endl;
		exit(0);
	}
	gameMap->setName(mapPath);
	// read the file until the end
	while (!mapReader.eof())
	{
		getline(mapReader, line, '\n');
		// read continent info, adding all continents
		if (line == "[Continents]")
		{
			s = "=";
			name = "";
			int num = 0;
			while (line == "" || line == "[Continents]")
				getline(mapReader, line, '\n');
			while (line != "")
			{
				replace(line.begin(), line.end(), ' ', '_');
				int len = line.length();
				string::size_type pos = line.find(s);
				name = line.substr(0, pos);
				num = stoi(line.substr(pos + 1, len - pos), nullptr);
				Continent *c = new Continent(name, num);
				gameMap->addContinent(c);
				getline(mapReader, line, '\n');
			}
			cout << endl;
		}
		/*read territory info, adding all territories
		 * any territories will be added when first occurs as neighbour of another one
		 * then update the info when read to line of previously added territory
		 */
		else if (line == "[Territories]")
		{
			s = ",";
			name = "";
			while (!mapReader.eof())
			{
				getline(mapReader, line, '\n');
				if (line == "")
					continue;
				vector<string> tInfo;
				replace(line.begin(), line.end(), ' ', '_');
				int start = 0;
				int end = 0;
				int len = line.length();
				string tempName;
				string d = ",";
				while (end >= 0)
				{
					end = line.find(d);
					tInfo.push_back(line.substr(start, end));
					line = line.substr(end + 1, len - end + 1);
				}
				replace(tInfo[3].begin(), tInfo[3].end(), ' ', '_');
				Territory *t = new Territory(tInfo[0], stoi(tInfo[1], nullptr), stoi(tInfo[2], nullptr), gameMap->getContinent(tInfo[3]));
				bool toDelete = false;
				// if the territory already exists, then update the existing one and delete the new one later
				if (gameMap->territoryExists(t->getName()))
				{
					gameMap->updateTerritory(t);
					toDelete = true;
				}
				else
					gameMap->addTerritory(t);
				for (int i = 4; i < tInfo.size(); i++)
				{
					replace(tInfo[i].begin(), tInfo[i].end(), ' ', '_');
					if (gameMap->territoryExists(tInfo[i]))
					{
						gameMap->getTerritory(t->getName())->addNeighbour(gameMap->getTerritory(tInfo[i]));
					}
					else
					{
						Territory *newTerritory = new Territory(tInfo[i]);
						gameMap->addTerritory(newTerritory);
						gameMap->getTerritory(t->getName())->addNeighbour(newTerritory);
					}
				}
				if (toDelete)
					delete t;
			}
		}
	}
	mapReader.close();
	// if no valid info for the map then return null pointer
	if (gameMap->getTerritoryNum() <= 0)
	{
		cout << "Invalid map file" << endl;
		return nullptr;
	}
	/*showing map is successfully loaded, then validate the map
	 * if not valid return null pointer
	 */
	else
	{
		//cout << "map loaded." << endl;
		return gameMap;
	}
}
