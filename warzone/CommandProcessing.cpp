#include "CommandProcessing.h"
#include "GameEngine.h"
#include <iostream>


CommandProcessor::CommandProcessor(GameEngine* game) {
	this->game = game;
}

void CommandProcessor::getCommand() {
	string command;
	command = readCommand();
	if(validate(command))
		saveCommand(command);
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
	if (command == "reply")
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
}

string CommandProcessor::stringToLog(){
	return "Command: ....+ getCommand()?";
}

Command::Command(string Command)
{

}

void Command::sideEffect()
{

}

void Command::saveEffect(string effect)
{
	Notify(this);
}

string Command::stringToLog() {
	
	return "Command issued: "<< getEffect();
}

void FileCommandProcessorAdapter::getCommand()
{

}

void FileLineReader::readLineFromFile()
{

}
