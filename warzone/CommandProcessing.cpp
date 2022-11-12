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

Command* CommandProcessor::getCommand() {
	string command;
	command = readCommand();
	if (command == "eof") {
		cout << "Error: End of file, no more lines";
		return;
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
	string c = command->getCommand();
	if ((c == "loadmap") && (state == "Start" || state == "Map Loaded"))
		return true;
	else if ((c == "validatemap") && (state == "Map Loaded"))
		return true;
	else if ((c == "addplayer") && (state == "Map Validated" || state == "Players Added"))
		return true;
	else if ((c == "gamestart") && (state == "Players Added"))
		return true;
	else if ((c == "replay") && (state == "Win"))
		return true;
	else if ((c == "quit") && (state == "Win"))
		return true;
	else {
		command->setEffect("Invalid Command.");
		return false;
	}
}

string CommandProcessor::readCommand()
{
	string command;
	cin >> command;
	return command;
}

void CommandProcessor::saveCommand(string command)
{
	this->lc.push_back(new Command(command));
	Notify(this);
}

string CommandProcessor::stringToLog(){
	return "Command have just saved: " + lc.back()->getCommand();
}

Command::Command(string Command)
{
	this->command = command;
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
	
	return "Command's Effect: " + getEffect() + "\nCommand: " + getCommand();
}

string Command::getEffect()
{
	return effect;
}

void Command::setEffect(string effect) {
	this->effect = effect;
}

string Command::getCommand()
{
	return command;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(GameEngine* game)
{
	CommandProcessor(new GameEngine());
	string path;
	cout << "Please enter the file name: ";
	cin >> path;
	this->flr = new FileLineReader(path);
	this->fileEnd = false;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(GameEngine* game)
{
	CommandProcessor(game);
	string path;
	cout << "Please enter the file name: ";
	cin >> path;
	this->flr = new FileLineReader(path);
	this->fileEnd = false;
}

bool FileCommandProcessorAdapter::getFileState() {
	return fileEnd;
}

void FileCommandProcessorAdapter::readCommand()
{
	string command;
	command = flr->readLineFromFile();
	if (command == "eof")
		this->fileEnd = false;
	saveCommand(command);
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