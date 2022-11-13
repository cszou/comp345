#include "CommandProcessing.h"
#include "GameEngine.h"
#include <iostream>
#include <fstream>
using std::ifstream;
using std::getline;


CommandProcessor::CommandProcessor()
{
	this->game = new GameEngine();
}

CommandProcessor::CommandProcessor(GameEngine* game) {
	this->game = game;
}

CommandProcessor::~CommandProcessor() {
	for (auto c : lc)
		delete c;
}

Command* CommandProcessor::getCommand() {
	cout << "this is getCommand() from cp" << endl;
	string command;
	command = readCommand();
	if (command == "eof") {
		cout << "Error: End of file, no more lines";
	}
	saveCommand(command);
	return lc.back();
}

void CommandProcessor::setGameEngine(GameEngine* game)
{
	this->game = game;
}

bool CommandProcessor::validate(Command* command)
{
	string state = game->getState();
	string c = command->getCommandString();
	if ((c == "loadmap") && (state == "Start" || state == "Map Loaded"))
	{
		cout << "This is a valid command." << endl;
		return true;
	}
	else if ((c == "validatemap") && (state == "Map Loaded"))
	{
		cout << "This is a valid command." << endl;
		return true;
	}
	else if ((c == "addplayer") && (state == "Map Validated" || state == "Players Added"))
	{
		cout << "This is a valid command." << endl;
		return true;
	}
	else if ((c == "gamestart") && (state == "Players Added"))
	{
		cout << "This is a valid command." << endl;
		return true;
	}
	else if ((c == "replay") && (state == "Win"))
	{
		cout << "This is a valid command." << endl;
		return true;
	}
	else if ((c == "quit") && (state == "Win"))
	{
		cout << "This is a valid command." << endl;
		return true;
	}
	else {
		cout << "This is not a valid command." << endl;
		command->setEffect("Invalid Command.");
		return false;
	}
}

string CommandProcessor::readCommand()
{
	cout << "this is readCommand() from cp" << endl;
	string command;
	cout << "Enter next command: ";
	cin >> command;
	return command;
}

void CommandProcessor::saveCommand(string command)
{
	this->lc.push_back(new Command(command));
	Notify(this);
}

string CommandProcessor::stringToLog() {
	return "Command have just saved: " + lc.back()->getCommandString();
}

Command::Command(string command)
{
	this->command = command;
}

Command::~Command() {
}

string Command::saveEffect()
{
	if (command == "loadmap")
		effect = "Map is loaded.";
	else if (command == "validatemap")
		effect = "Map is validated.";
	else if (command == "addplayer")
		effect = "Player is added.";
	else if (command == "gamestart")
		effect = "Game is started.";
	else if (command == "replay")
		effect = "Replay the game.";
	else if (command == "quit")
		effect = "Game is terminated.";
	else
		effect = "Invalid command.";
	Notify(this);
	return effect;
}

string Command::stringToLog() {

	return "Command's Effect: " + getEffect() + "\nCommand: " + getCommandString();
}

string Command::getEffect()
{
	return effect;
}

void Command::setEffect(string effect) {
	this->effect = effect;
}

string Command::getCommandString()
{
	return command;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(GameEngine* game) :CommandProcessor(game)
{
	string path;
	cout << "Please enter the file name: ";
	cin >> path;
	this->flr = new FileLineReader(path);
	this->fileEnd = false;
}

bool FileCommandProcessorAdapter::getFileState() {
	return fileEnd;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
}

string FileCommandProcessorAdapter::readCommand()
{
	string command;
	command = flr->readLineFromFile();
	if (command == "eof")
		this->fileEnd = false;
	return command;
}

FileLineReader::~FileLineReader() {
}

FileLineReader::FileLineReader(string path) {
	this->commandReader.open(path);
	while (!commandReader.is_open()) {
		cout << "failed to open " << path << endl;
		cout << "Please enter another file name: ";
		cin >> path;
	}
}

string FileLineReader::readLineFromFile()
{
	string line;
	if (!this->commandReader.eof()) {
		getline(commandReader, line, '\n');
		return line;
	}
	commandReader.close();
	return "eof";
}