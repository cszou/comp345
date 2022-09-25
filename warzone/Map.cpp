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

Territory::Territory(const Territory& t)
{
	this->numberOfArmies = t.numberOfArmies;
	this->coordX = t.coordX;
	this->coordY = t.coordY;
	this->owner = t.owner;
	this->continent = t.continent;
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

Continent::Continent(string name, int num) {
	this->numberOfTerritory = num;
	this->continentName = name;
}

Continent::Continent(const Continent& c)
{
	this->numberOfTerritory = c.numberOfTerritory;
	this, continentName = c.continentName;
}

Continent& Continent::operator=(Continent& c)
{
	this->numberOfTerritory = c.numberOfTerritory;
	this, continentName = c.continentName;
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

std::ostream& operator<<(std::ostream &strm, const Continent &c)
{
	return strm << "Continent name: " << c.continentName << " with " << c.numberOfTerritory << " territories.";
}

void loader()
{
	string line;
	string path;
	list<Continent> continents;
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
				continents.push_back(Continent::Continent(name, num));
				cout << continents.back() << endl;
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
				cout << line << endl;
				vector<string> tInfo;
				int start = 0;
				int end = 0;
				int len = line.length();
				string d = ",";
				while (end >= 0) {
					end = line.find(d);
					tInfo.push_back(line.substr(start, end));
					line = line.substr(end + 1, len - end + 1);
					cout << tInfo.back() << endl;
				}
			}
		}
	}
	mapReader.close();
}
