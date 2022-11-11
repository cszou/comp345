#include "CommandProcessing.h"
#include <iostream>

void CommandProcessor::getCommand() {
	string command;
	std::cin >> command;
	lc.push_back(new Command(command));
	validate(command);
}

bool CommandProcessor::validate(string command)
{
	return false;
}

void CommandProcessor::readCommand()
{
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

void Command::saveCommand(string command)
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
