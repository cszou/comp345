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
	CommandProcessor(const CommandProcessor& cp);
	~CommandProcessor();
	Command* getCommand();
	void setGameEngine(GameEngine* game);
	bool validate(Command* command);
	friend ostream& operator << (ostream& ostream, const CommandProcessor& cp);

	//Define stringToLog method from abstract base class ILoggable
	string stringToLog();
private:
	virtual string readCommand();
	void saveCommand(string command);
	vector<Command*> lc;
protected:
	GameEngine* game;
};

class Command : public ILoggable, public Subject{
public:
	Command(string Command);
	Command(const Command& c);
	~Command();
	string saveEffect();
	
	//Define stringToLog method from abstract base class ILoggable
	string stringToLog();
	string getEffect();
	void setEffect(string effect);
	string getCommandString();
	friend ostream& operator << (ostream& ostream, const Command& c);
private:
	string command;
	string effect;
};

class FileCommandProcessorAdapter:public CommandProcessor{
public:
	FileCommandProcessorAdapter();
	FileCommandProcessorAdapter(GameEngine* game);
	FileCommandProcessorAdapter(const FileCommandProcessorAdapter& fcp);
	~FileCommandProcessorAdapter();
	bool getFileState();
	friend ostream& operator << (ostream& ostream, const FileCommandProcessorAdapter& fcp);
private:
	string readCommand();
	FileLineReader* flr;
	bool fileEnd;
};

class FileLineReader {
public:
	FileLineReader(string path);
	~FileLineReader();
	string readLineFromFile();
private:
	ifstream commandReader;
};
