#pragma once
#include <vector>
using std::vector;
#include <string>
using std::string;

class CommandProcessor {
public:
	void getCommand();
private:
	bool validate(string command);
	void readCommand();
	vector<Command*> lc;
};

class Command {
public:
	Command(string Command);
	void sideEffect();
	void saveCommand(string command);
	void saveEffect(string effect);
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