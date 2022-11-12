#pragma once
#include <vector>
using std::vector;
#include <string>
using std::string;
#include "LoggingObserver.h"
#include "GameEngine.h"

class CommandProcessor : public ILoggable, public Subject {
public:
	CommandProcessor(GameEngine* game);
	void getCommand();
	
	//Define stringToLog method from abstract base class ILoggable
	string stringToLog();
private:
	bool validate(string command);
	string readCommand();
	void saveCommand(string command);
	GameEngine* game;
	vector<Command*> lc;
};

class Command : public ILoggable, public Subject{
public:
	Command(string Command);
	void sideEffect();
	void saveEffect(string effect);
	
	//Define stringToLog method from abstract base class ILoggable
	string stringToLog();
private:
	string command;
	string effect;
};

class FileCommandProcessorAdapter:public CommandProcessor{
public:
	void getCommand();
private:
	bool validate();
	void readCommand();
	vector<Command*> lc;
	FileLineReader flr;
};

class FileLineReader {
	void readLineFromFile();
};
