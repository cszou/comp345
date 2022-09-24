#pragma once

class Map {
public:
	Map(const Map& m);
	void loader();
	void validate();
	Map& operator =(const Map& m);
private:
	void validate();
	Territory t1;
};

class Territory {
public:
	Territory() {};
	Territory(const Territory& t);
	Territory& operator =(const Territory& t);
	void setOwner(string anOwner);
	string getOwner();
	void setNumberOfArmies(int numOfArmies);
	int getNumberOfArmies();
private:
	string owner;
	int numberOfArmies;
	int coordX;
	int coordY;
	string contient;
};

class Continent {
public:
	Continent() {};
	Continent(const Continent& c);
	Continent& operator =(Continent& c);
	Territory* getTerritories();
private:
	Territory* t[];
};

