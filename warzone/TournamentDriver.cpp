#include "TournamentDriver.h"
#include "GameEngine.h"
#include "CommandProcessing.h"
#include "Player.h"
#include <iostream>
using std::cin;
using std::cout;
#include <string>
using std::string;
#include <vector>
using std::vector;

void testTournament()
{
	GameEngine* game = new GameEngine();
	cout << "Where do you want to read commands from? 1. console / 2. file: ";
	string ans;
	cin >> ans;
	if (ans == "1" || ans == "console")
		// read from console
	{
		while (!game->checkTournamentMode())
		{
			cout << "Please enter a valid tournament command.\n";
			CommandProcessor* cp = new CommandProcessor(game);
			cp->getCommand();
		}
	}
	else if (ans == "2" || ans == "file")
		// read from file
	{
		while (!game->checkTournamentMode())
		{
			cout << "Please enter a valid tournament command.\n";
			CommandProcessor* fcp = new FileCommandProcessorAdapter(game);
			fcp->getCommand();
		}
	}
	// vector to record the winners
	vector<string> winners;
	//Game start command
	for(auto m: game->tournamentMaps){
		game->map = m;
		cout << "******************** Start map: " << m->getName() << " ********************\n";
		for(int i = 0; i < game->numOfGame; i++)
		{
			cout << "******************** Game " << i + 1 << " ********************\n";
			for (auto p : game->playersList)
				p->reset();

			//auto rng = std::default_random_engine{};
			vector<Territory*> allTerritories = game->map->getAllTerritories();
			std::random_shuffle(std::begin(allTerritories), std::end(allTerritories));
			//Distribute territories to players
			while (!allTerritories.empty()) {
				for (int i = 0; i < game->playersList.size(); i++) {
					if (allTerritories.empty())
						break;
					game->playersList[i]->addTerritory(allTerritories.back());
					allTerritories.pop_back();
				}
			}
			cout << "all territory assigned" << endl;
			//Creating random player order, this is the order of play
			std::random_shuffle(std::begin(game->playersList), std::end(game->playersList));

			//Assign reinforcement to each player
			for (auto p : game->playersList) {
				p->setReinforcement(10);
				p->set_all_territories(allTerritories);
			}

			//get continents
			vector<Continent*> continents = game->map->getAllContinents();

			int turn = 1;
			int numOfPlayers = game->playersList.size();
			while (numOfPlayers > 1 && turn <= game->maxNumberOfTurns) {
				cout << "\n******************** round " << turn << " ********************" << endl;
				// assign troops
				for (auto p : game->playersList) {
					if (p->checkEliminated() || p->getTerriotory().empty())
						continue;
					else {
						//Assign troops based on the number of territories
						vector<Territory*> playerTerritories = p->getTerriotory();
						int num_Troop_base;
						num_Troop_base = playerTerritories.size() / 3;
						int num_Troop = num_Troop_base > 3 ? num_Troop_base : 3;
						//Assign continent bonus
						for (auto c : game->map->getAllContinents())
							if (c->ownedBy(p))
								num_Troop += c->getBonus();
						p->setReinforcement(num_Troop);
					}
				}
				for (auto p : game->playersList)
					if (p->checkEliminated() || p->getTerriotory().empty())
						continue;
					else
					{
						p->issueOrder("Deploy");
					}

				for (auto p : game->playersList)
					if (p->checkEliminated() || p->getTerriotory().empty())
						continue;
					else
					{
						cout << "\n********** " << p->getName() << "'s turn to advance **********\n";
						cout << p->getName() << " has " << p->getTerriotory().size() << " territories before advance.\n";
						p->issueOrder("Advance");
						cout << p->getName() << " has " << p->getTerriotory().size() << " territories after advance.\n";
					}

				for (auto p : game->playersList)
					if (p->checkEliminated())
						continue;
					else if (p->getTerriotory().empty())
					{
						p->eliminated();
						numOfPlayers -= 1;
					}
				turn += 1;
			}
			cout << "\n******************** Game Ended ********************\n";
			cout << turn - 1 << " rounds played with " << numOfPlayers << " players left.\n";
			if (numOfPlayers == 1)
			{
				for(auto p: game->playersList)
					if(p->getTerriotory().size()>0)
					{
						cout << "The game has ended, the winner is " << p->getName() << endl << endl;
						winners.push_back(p->getName());
					}
			}
			else
			{
				cout << "The game has ended as a draw" << endl << endl;
				winners.push_back("Draw");
			}
		}
	}
	cout << endl;
	string output = "tournamentlog.txt";
	fstream filestream;
	//if the file does not exit, it will create a new file. Otherwise, append content to the file
	filestream.open(output, ofstream::app);
	cout << "\nTournament Mode:\n";
	filestream << "\nTournament Mode:\n";
	cout << "M: ";
	filestream << "M: ";
	for (auto m : game->tournamentMaps)
	{
		cout << m->getName() << " ";
		filestream << m->getName() << " ";
	}
	cout << "\nP: ";
	filestream << "\nP: ";
	for (auto p : game->playersList)
	{
		cout << p->getName() << " ";
		filestream << p->getName() << " ";
	}
	cout << "\nG: " << game->numOfGame << "\nD: " << game->maxNumberOfTurns << endl;
	filestream << "\nG: " << game->numOfGame << "\nD: " << game->maxNumberOfTurns << endl;
	cout << "\nResults:\n";
	filestream << "\nResults:\n";
	for (int i = 0;i < 20;i++)
	{
		cout << " ";
		filestream << " ";
	}
	for (int i = 1;i <= game->numOfGame;i++)
	{
		cout << "Game " << i;
		filestream << "Game " << i;
		for (int i = 0;i < 14;i++)
		{
			cout << " ";
			filestream << " ";
		}
	}
	int j = 0;
	for (auto m : game->tournamentMaps) {
		cout << endl << m->getName();
		filestream << endl << m->getName();
		for (int i = m->getName().size();i < 20;i++)
		{
			cout << " ";
			filestream << " ";
		}
		cout << winners[j];
		filestream << winners[j];
		for (int i = winners[j].size();i < 20;i++)
		{
			cout << " ";
			filestream << " ";
		}
		j += 1;
		while (j % game->numOfGame != 0)
		{
			cout << winners[j];
			filestream << winners[j];
			for (int i = winners[j].size();i < 20;i++)
			{
				cout << " ";
				filestream << " ";
			}
			j += 1;
		}
	}
	cout << endl;
	filestream << endl;
	//close the file
	filestream << "-----------------------------------------\n" << endl;
	filestream.close();
}