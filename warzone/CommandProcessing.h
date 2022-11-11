#pragma once
#include <vector>
using std::vector;
#include <string>
using std::string;
#include "LoggingObserver.h"
class CommandProcessor : public ILoggable, public Subject {
public:
	void getCommand();
	
	//Define stringToLog method from abstract base class ILoggable
	string stringToLog();
private:
	bool validate(string command);
	void readCommand();
	vector<Command*> lc;
};

class Command : public ILoggable, public Subject{
public:
	Command(string Command);
	void sideEffect();
	void saveCommand(string command);
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
