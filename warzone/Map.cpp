#include "Map.h"
#include <iostream>
using namespace std;

Map::Map(const Map& aMAp)
{

}

void Map::loader()
{
}

void Map::validate()
{
}

Map& Map::operator=(const Map& m)
{
	// TODO: insert return statement here
}

Territory::Territory(const Territory& aTerritory)
{
}

Territory& Territory::operator=(const Territory& t)
{
	// TODO: insert return statement here
}

void Territory::setOwner(string anOwner)
{
	this->owner = anOwner;
}

string Territory::getOwner()
{
	return this->owner;
}

void Territory::setNumberOfArmies(int numOfArmies)
{
	this->numberOfArmies = numOfArmies;
}

int Territory::getNumberOfArmies()
{
	return this->numberOfArmies;
}

Continent::Continent(const Continent& aContinent)
{
}

Continent& Continent::operator=(Continent& c)
{
	// TODO: insert return statement here
}

Territory* Continent::getTerritories()
{
	return nullptr;
}
