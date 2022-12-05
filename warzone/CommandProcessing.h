#pragma once
#include <vector>
using std::vector;
#include <string>
using std::string;
#include "LoggingObserver.h"
#include "GameEngine.h"
class Command;
class FileLineReader;

// command processor, get command from console
class CommandProcessor : public ILoggable, public Subject {
public:
	CommandProcessor(); // constructor with no arguments
	CommandProcessor(GameEngine* game); // connect with existing game engine
	CommandProcessor(const CommandProcessor& cp); // copy constructor
	~CommandProcessor(); // destructor
	Command* getCommand(); // get a command from console
	void setGameEngine(GameEngine* game); //set a geme engine
	bool validate(Command* command); //validate a command
	friend ostream& operator << (ostream& ostream, const CommandProcessor& cp); //stream insertion

	//Define stringToLog method from abstract base class ILoggable
	string stringToLog();
private:
	virtual string readCommand(); // read the command got from getCommand()
	void saveCommand(string command); // save the command
	vector<Command*> lc; //a list of commands
protected:
	GameEngine* game; // the game engine
	bool validateTournamentCommand(vector<string> c);
};

// command class to store a command
class Command : public ILoggable, public Subject{
public:
	Command(); //default constructor
	Command(string Command); // constructor with command name
	Command(const Command& c); // copy constructor
	~Command(); // destructor
	string saveEffect(); // save the effect of the command
	
	//Define stringToLog method from abstract base class ILoggable
	string stringToLog();
	string getEffect(); // get the efffect of the command
	void setEffect(string effect); // set command effect
	string getCommandString(); //get the command name
	friend ostream& operator << (ostream& ostream, const Command& c); //stream insertion
private:
	string command; // string to store the command name
	string effect; // string to store the command effect
};

//subclass of CommandProcessor as an adapter for reading from file
class FileCommandProcessorAdapter:public CommandProcessor{
public:
	FileCommandProcessorAdapter(); //default constructor
	FileCommandProcessorAdapter(GameEngine* game); // connect with existing game engine
	FileCommandProcessorAdapter(const FileCommandProcessorAdapter& fcp); //copy constructor
	~FileCommandProcessorAdapter(); // desctructor
	bool getFileState(); //get the file state
	friend ostream& operator << (ostream& ostream, const FileCommandProcessorAdapter& fcp); //stream insertion
private:
	string readCommand(); //overriding read the command from getCommand()
	FileLineReader* flr; // FlieLineReader object for reading from file
	bool fileEnd; // indicate end of file
};

class FileLineReader {
public:
	FileLineReader(string path); // constructor with the file path
	~FileLineReader(); //destructor
	string readLineFromFile(); //read line by line
private:
	ifstream commandReader; // file stream
};
