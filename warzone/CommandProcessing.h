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
	~CommandProcessor();
	void getCommand();
	void saveCommand(string command);
	void setGameEngine(GameEngine* game);
	
	//Define stringToLog method from abstract base class ILoggable
	string stringToLog();
private:
	void readCommand();
	bool validate(Command* command);
	void saveCommand(string command);
	GameEngine* game;
	vector<Command*> lc;
};

class Command : public ILoggable, public Subject{
public:
	Command(string Command);
	~Command();
	string saveEffect();
	
	//Define stringToLog method from abstract base class ILoggable
	string stringToLog();
	string getEffect();
	void setEffect(string effect);
	string getCommand();
private:
	string command;
	string effect;
};

class FileCommandProcessorAdapter:public CommandProcessor{
public:
	FileCommandProcessorAdapter(GameEngine* game, string file);
	~FileCommandProcessorAdapter();
	void getCommand();
private:
	void readCommand();
	FileLineReader* flr;
};

class FileLineReader {
public:
	FileLineReader(string path);
	~FileLineReader();
	string readLineFromFile();
private:
	ifstream commandReader;
};
