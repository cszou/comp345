#include "CommandProcessing.h"
#include "GameEngine.h"
#include <iostream>
#include <fstream>
using std::ifstream;
using std::getline;
#include "PlayerStrategies.h"

// constructor with no arguments
CommandProcessor::CommandProcessor()
{
	this->game = new GameEngine();
}

// connect with existing game engine
CommandProcessor::CommandProcessor(GameEngine* game) {
	this->game = game;
}

// copy constructor
CommandProcessor::CommandProcessor(const CommandProcessor& cp) {
	this->game = new GameEngine(*cp.game);
}

// destructor
CommandProcessor::~CommandProcessor() {
	for (auto c : lc)
		delete c;
}

// get a command from console
Command* CommandProcessor::getCommand() {
	string command;
	command = readCommand();
	saveCommand(command);
	return lc.back();
}

//set a geme engine
void CommandProcessor::setGameEngine(GameEngine* game)
{
	this->game = game;
}

/*validate a command compare with the game state
if valid, change the game state*/
bool CommandProcessor::validate(Command* command)
{
	string state = game->getState();
	string c = command->getCommandString();
	if ((c == "tournament")) {
		game->enableTournamentMode();
	}
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
		if (game->map->validate()) {
			cout << "This is a valid map." << endl;
			game->setState("Map Validated");
			cout << "Transitions to mapvalidated state" << endl << endl;
		}
		else {
			cout << "This is not a valid map." << endl;
			cout << "State does not change" << endl << endl;
		}
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

// read the command got from getCommand() also get map and palyer if required
string CommandProcessor::readCommand()
{
	string command = "";
	cout << "Enter next command: ";
	while (command == "")
		getline(cin, command);
	vector<string> commands;
	int start = 0;
	int end = 0;
	int len = command.length();
	string tempName;
	string d = " ";
	while (end >= 0) {
		end = command.find(d);
		commands.push_back(command.substr(start, end));
		command = command.substr(end + 1, len - end + 1);
	}
	if (commands[0] == "tournament")
		if (this->validateTournamentCommand(commands))
		{
			cout << "valid tournament command.\n";
			game->enableTournamentMode();
		}
		else
		{
			cout << "invalid tournament command.\n";
			return "error tournament command";
		}
	else if (commands[0] == "loadmap") {
		if (commands.size() < 2)
			return "error loadmap command";
		else
			game->readMap(commands[1]);
	}
	else if (commands[0] == "addplayer") {
		if (commands.size() < 2)
			return "error addplayer command";
		else
			game->addPlayer(commands[1]);
	}
	return commands[0];
}

// save the command
void CommandProcessor::saveCommand(string command)
{
	this->lc.push_back(new Command(command));
	Notify(this);
}

bool CommandProcessor::validateTournamentCommand(vector<string> c)
{
	// clear all players, maps and related info in GemeEngine to start a new tournament
	game->playersList.clear();
	game->tournamentMaps.clear();
	game->numOfGame = 0;
	game->maxNumberOfTurns = 0;
	// parsing the input and validate it
	int i = 1;
	int size = c.size();
	MapLoader* mapLoader = new MapLoader();
	// temp player and map for reading
	Map* tempMap;
	Player* tempPlayer;
	while (i < size) {
		if (c[i] == "-M")
		{
			i += 1;
			while (c[i] != "-P") {
				tempMap = mapLoader->readMap(c[i]);
				if (tempMap->validate())
					game->tournamentMaps.push_back(tempMap);
				i += 1;
			}
			if (game->tournamentMaps.size() < 1 || game->tournamentMaps.size() > 5)
				return false;
		}
		if (c[i] == "-P")
		{
			i += 1;
			while (c[i] != "-G") {
				if (c[i] == "aggressive" || c[i] == "Aggressive")
				{
					tempPlayer = new Player("Aggressive");
					tempPlayer->setPlayerStrategy(new AggressivePlayerStrategy(tempPlayer));
					game->addPlayer(tempPlayer);
				}
				else if (c[i] == "benevolent" || c[i] == "Benevolent")
				{
					tempPlayer = new Player("Benevolent");
					tempPlayer->setPlayerStrategy(new BenevolentPlayerStrategy(tempPlayer));
					game->addPlayer(tempPlayer);
				}
				else if (c[i] == "cheater" || c[i] == "Cheater")
				{
					tempPlayer = new Player("Cheater");
					tempPlayer->setPlayerStrategy(new CheaterPlayerStrategy(tempPlayer));
					game->addPlayer(tempPlayer);
				}
				else if (c[i] == "neutral" || c[i] == "Neutral")
				{
					tempPlayer = new Player("Neutral");
					tempPlayer->setPlayerStrategy(new NeutralPlayerStrategy(tempPlayer));
					game->addPlayer(tempPlayer);
				}
				else
					return false;
				i += 1;
			}
			if (game->playersList.size() < 2 || game->playersList.size() > 4)
				return false;
		}
		if (c[i] == "-G")
		{
			i += 1;
			game->numOfGame = stoi(c[i++]);
			if (game->numOfGame > 5 || game->numOfGame < 1)
				return false;
		}
		if (c[i] == "-D")
		{
			i += 1;
			game->maxNumberOfTurns = stoi(c[i++]);
			if (game->maxNumberOfTurns > 50 || game->maxNumberOfTurns < 10)
				return false;
		}
	}
	delete mapLoader;
	return true;
}

// stringToLog method from abstract base class ILoggable
string CommandProcessor::stringToLog() {
	return "Command have just saved: " + lc.back()->getCommandString();
}

//default constructor
Command::Command()
{
	this->effect = "";
	this->command = "";
}

// constructor with command name
Command::Command(string command)
{
	this->command = command;
}

// copy constructor
Command::Command(const Command& c)
{
	this->command = c.command;
	this->effect = c.effect;
}

// destructor
Command::~Command() {
}

// save the effect of the command
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

// stringToLog method from abstract base class ILoggable
string Command::stringToLog() {

	return "Command: " + getCommandString() + "\nCommand's Effect: " + getEffect();
}

// get the efffect of the command
string Command::getEffect()
{
	return effect;
}

// set command effect
void Command::setEffect(string effect) {
	this->effect = effect;
}

//get the command name
string Command::getCommandString()
{
	return command;
}

//default constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter()
{
	this->game = new GameEngine();
	string path;
	cout << "Please enter the file name: ";
	cin >> path;
	this->flr = new FileLineReader(path);
	this->fileEnd = false;
}

// connect with existing game engine
FileCommandProcessorAdapter::FileCommandProcessorAdapter(GameEngine* game) :CommandProcessor(game)
{
	string path;
	cout << "Please enter the file name: ";
	cin >> path;
	this->flr = new FileLineReader(path);
	this->fileEnd = false;
}

//copy constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& fcp) : CommandProcessor(fcp.game) {
	this->fileEnd = fcp.fileEnd;
	this->flr = fcp.flr;
}

//get the file state
bool FileCommandProcessorAdapter::getFileState() {
	return fileEnd;
}

// desctructor
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
}

//overriding read the command from getCommand(), get command from file
string FileCommandProcessorAdapter::readCommand()
{
	string commands;
	commands = flr->readLineFromFile();
	cout << commands << endl;
	vector<string> command;
	int start = 0;
	int end = 0;
	int len = commands.length();
	string tempName;
	string d = " ";
	while (end >= 0) {
		end = commands.find(d);
		command.push_back(commands.substr(start, end));
		commands = commands.substr(end + 1, len - end + 1);
	}
	if (command[0] == "tournament")
		if (this->validateTournamentCommand(command))
		{
			cout << "valid tournament command.\n";
			game->enableTournamentMode();
		}
		else
		{
			cout << "invalid tournament command.\n";
			return "error tournament command";
		}
	else if (command[0] == "loadmap") {
		if (command.size() < 1)
			return "error command";
		else
			game->readMap(command[1]);
	}
	else if (command[0] == "addplayer") {
		if (command.size() < 1)
			return "error command";
		else
			game->addPlayer(command[1]);
	}
	return command[0];
	if (command[0] == "eof") {
		this->fileEnd = true;
		cout << "Error: End of file, no more lines";
	}
	return command[0];
}

//destructor
FileLineReader::~FileLineReader() {
}

// constructor with the file path
FileLineReader::FileLineReader(string path) {
	this->commandReader.open(path);
	while (!commandReader.is_open()) {
		cout << "failed to open " << path << endl;
		cout << "Please enter another file name: ";
		cin >> path;
		this->commandReader.open(path);
	}
}

//read line by line
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

//stream insertion
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
