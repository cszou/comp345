#pragma once
#include <vector>
using std::vector;
#include <string>
using std::string;
#include "LoggingObserver.h"
#include "GameEngine.h"
class Command;
class FileLineReader;

class CommandProcessor : public ILoggable, public Subject {
public:
	CommandProcessor();
	CommandProcessor(GameEngine* game);
	~CommandProcessor();
	Command* getCommand();
	void setGameEngine(GameEngine* game);

	//Define stringToLog method from abstract base class ILoggable
	string stringToLog();
private:
	string readCommand();
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

//class FileCommandProcessorAdapter:public CommandProcessor{
//public:
//	FileCommandProcessorAdapter();
//	FileCommandProcessorAdapter(GameEngine* game);
//	~FileCommandProcessorAdapter();
//	bool getFileState();
//private:
//	string readCommand();
//	FileLineReader* flr;
//	bool fileEnd;
//};
//
//class FileLineReader {
//public:
//	FileLineReader(string path);
//	~FileLineReader();
//	string readLineFromFile();
//private:
//	ifstream commandReader;
//};
