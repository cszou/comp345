#pragma once
#include <vector>
using std::vector;
#include <string>
using std::string;
#include "LoggingObserver.h"
#include "GameEngine.h"

class CommandProcessor : public ILoggable, public Subject {
public:
	CommandProcessor();
	CommandProcessor(GameEngine* game);
	void getCommand();
	void setGameEngine(GameEngine* game);
	
	//Define stringToLog method from abstract base class ILoggable
	string stringToLog();
private:
	string readCommand();
	bool validate(string command);
	void saveCommand(string command);
	GameEngine* game;
	vector<Command*> lc;
};

class Command : public ILoggable, public Subject{
public:
	Command(string Command);
	string saveEffect(string effect);
	
	//Define stringToLog method from abstract base class ILoggable
	string stringToLog();
	string getEffect();
private:
	string command;
	string effect;
};

class FileCommandProcessorAdapter:public CommandProcessor{
public:
	FileCommandProcessorAdapter(GameEngine* game, string file);
private:
	void readCommand();
	FileLineReader* flr;
};

class FileLineReader {
public:
	FileLineReader();
private:
	void readLineFromFile();
};
