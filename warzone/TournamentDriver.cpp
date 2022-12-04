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
	while (!game->checkTournamentMode())
	{
		cout << "Please enter a valid tournament command.\n";
		CommandProcessor* cp = new CommandProcessor(game);
		cp->getCommand();
	}
	//Game start command
	for(auto m: game->tournamentMaps){
		game->map = m;
		for(int i = 0; i < game->numOfGame; i++)
		{
			for (auto p : game->playersList)
				p->reset();

			auto rng = std::default_random_engine{};
			vector<Territory*> allTerritories = game->map->getAllTerritories();
			std::shuffle(std::begin(allTerritories), std::end(allTerritories), rng);
			//Distribute territories to players
			while (!allTerritories.empty()) {
				for (int i = 0; i < game->playersList.size(); i++) {
					if (allTerritories.empty())
						break;
					game->playersList[i]->addTerritory(allTerritories.back());
					allTerritories.pop_back();
				}
			}

			//Creating random player order, this is the order of play
			
			std::shuffle(std::begin(game->playersList), std::end(game->playersList), rng);

			//Assign reinforcement to each player
			for (auto p : game->playersList) {
				p->setReinforcement(50);
				p->set_all_territories(allTerritories);
				p->gethandofcard()->add_CardinHand(game->deck->draw());
			}

			//Add players and get continents and territories
			vector<Continent*> continents = game->map->getAllContinents();
			// vector to record the winners
			vector<string> winners;

			int turn = 1;
			int numOfPlayers = game->playersList.size();
			while (numOfPlayers > 1 && turn <= game->maxNumberOfTurns) {

				// assign troops
				for (auto p : game->playersList) {
					if (p->checkEliminated())
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
					if (p->checkEliminated())
						continue;
					else
						p->issueOrder("deploy");

				for (auto p : game->playersList)
					if (p->checkEliminated())
						continue;
					else
						p->issueOrder("advance");

				for (auto p : game->playersList)
					if (p->getTerriotory().empty())
					{
						p->eliminated();
						numOfPlayers -= 1;
					}
				turn += 1;
			}
			if (numOfPlayers == 1)
			{
				cout << "The game has ended, the winner is  " << game->playersList[0]->getName() << endl;
				winners.push_back(game->playersList[0]->getName());
			}
			else
			{
				cout << "The game has ended as a draw" << endl;
				winners.push_back("Draw");
			}
		}
	}
}