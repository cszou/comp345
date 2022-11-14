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

CommandProcessor::CommandProcessor(const CommandProcessor& cp) {
	this->game = new GameEngine(*cp.game);
}

CommandProcessor::~CommandProcessor() {
	for (auto c : lc)
		delete c;
}

Command* CommandProcessor::getCommand() {
	string command;
	command = readCommand();
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
		game->setState("Map Loaded");
		cout << "Transitions to maploaded state" << endl << endl;
		return true;
	}
	else if ((c == "validatemap") && (state == "Map Loaded"))
	{
		cout << "This is a valid command." << endl;
		game->setState("Map Validated");
		cout << "Transitions to mapvalidated state" << endl << endl;
		return true;
	}
	else if ((c == "addplayer") && (state == "Map Validated" || state == "Players Added"))
	{
		cout << "This is a valid command." << endl;
		game->setState("Players Added");
		cout << "Transitions to playersadded state" << endl << endl;
		return true;
	}
	else if ((c == "gamestart") && (state == "Players Added"))
	{
		cout << "This is a valid command." << endl;
		game->setState("Assign Reinforcement");
		cout << "Transitions to assignreinforcement state" << endl << endl;
		return true;
	}
	else if ((c == "replay") && (state == "Win"))
	{
		cout << "This is a valid command." << endl;
		game->setState("Start");
		cout << "Transitions to start state" << endl << endl;
		return true;
	}
	else if ((c == "quit") && (state == "Win"))
	{
		cout << "This is a valid command." << endl;
		game->setState("Terminated");
		cout << "Exit Program" << endl << endl;
		return true;
	}
	else {
		cout << "This is not a valid command." << endl << endl;
		command->setEffect("Invalid Command.");
		return false;
	}
}

string CommandProcessor::readCommand()
{
	string command;
	cout << "Enter next command: ";
	cin >> command;
	if (command == "loadmap") {
		string mapName;
		cout << "please enter map name: ";
		cin >> mapName;
		game->readMap(mapName);
	}
	else if (command == "addplayer") {
		cout << "Please enter player name: ";
		string playerName;
		cin >> playerName;
		game->addPlayer(playerName);
	}
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

Command::Command()
{
	this->effect = "";
	this->command = "";
}

Command::Command(string command)
{
	this->command = command;
}

Command::Command(const Command& c)
{
	this->command = c.command;
	this->effect = c.effect;
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

	return "Command: " + getCommandString()+ "\nCommand's Effect: " + getEffect() ;
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

FileCommandProcessorAdapter::FileCommandProcessorAdapter()
{
	this->game = new GameEngine();
	string path;
	cout << "Please enter the file name: ";
	cin >> path;
	this->flr = new FileLineReader(path);
	this->fileEnd = false;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(GameEngine* game) :CommandProcessor(game)
{
	string path;
	cout << "Please enter the file name: ";
	cin >> path;
	this->flr = new FileLineReader(path);
	this->fileEnd = false;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& fcp): CommandProcessor(fcp.game) {
	this->fileEnd = fcp.fileEnd;
	this->flr = fcp.flr;
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
	cout << command << endl;
	if (command == "eof") {
		this->fileEnd = false;
		cout << "Error: End of file, no more lines";
	}
	else if (command == "loadmap") {
		string mapName = flr->readLineFromFile();
		game->readMap(mapName);
	}
	else if (command == "addplayer") {
		string playerName = flr->readLineFromFile();
		game->addPlayer(playerName);
	}
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

ostream& operator<<(ostream& strm, const CommandProcessor& cp)
{
	return strm << "this is a command processor." << endl;
}

ostream& operator<<(ostream& strm, const Command& c)
{
	return strm << "this is a" << c.command << "command." << endl;
}

ostream& operator<<(ostream& strm, const FileCommandProcessorAdapter& fcp)
{
	return strm << "this is a command processor from file." << endl;
}
