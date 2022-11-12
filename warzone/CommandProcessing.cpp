#include "CommandProcessing.h"
#include "GameEngine.h"
#include <iostream>


CommandProcessor::CommandProcessor()
{
	this->game = nullptr;
}

CommandProcessor::CommandProcessor(GameEngine* game) {
	this->game = game;
}

void CommandProcessor::getCommand() {
	string command;
	command = readCommand();
	if(validate(command))
		saveCommand(command);
}

void CommandProcessor::setGameEngine(GameEngine* game)
{
	this->game = game;
}

bool CommandProcessor::validate(string command)
{
	string state = game->getState();
	if (command == "loadmap")
		if (state == "Start" || state == "Map Loaded")
			return true;
		else
			return false;
	if (command == "validatemap")
		if (state == "Map Loaded")
			return true;
		else
			return false;
	if (command == "addplayer")
		if (state == "Map Validated" || state =="Players Added")
			return true;
		else
			return false;
	if (command == "gamestart")
		if (state == "Players Added")
			return true;
		else
			return false;
	if (command == "replay")
		if (state == "Win")
			return true;
		else
			return false;
	if (command == "quit")
		if (state == "Win")
			return true;
		else
			return false;
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
	return "Command have just saved: " + lc.back ->getCommand();
}

Command::Command(string Command)
{
	this->command = command;
}

string Command::saveEffect(string effect)
{
	if (command == "loadmap")
		effect = "Map is loaded.";
	if (command == "validatemap")
		effect = "Map is validated.";
	if (command == "addplayer")
		effect = "Player is added.";
	if (command == "gamestart")
		effect = "Game is started.";
	if (command == "replay")
		effect = "Replay the game.";
	if (command == "quit")
		effect = "Game is terminated.";
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
string Command::getCommand(){
	return command;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(GameEngine* game, string file)
{
	CommandProcessor(game);
}

void FileCommandProcessorAdapter::readCommand()
{
	
}

void FileLineReader::readLineFromFile()
{

}
