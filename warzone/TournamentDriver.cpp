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
			vector<Territory*> allTerritories = game->map->getAllTerritories();

			//Distribute territories to players
			while (!allTerritories.empty()) {
				for (int i = 0; i < game->playerList.size(); i++) {
					if (allTerritories.empty())
						break;
					game->playerList[i]->addTerritory(allTerritories.back());
					allTerritories.pop_back();
				}
			}

			//Creating random player order, this is the order of play
			auto rng = std::default_random_engine{};
			std::shuffle(std::begin(game->playerList), std::end(game->playerList), rng);

			//Assign reinforcement to each player
			for (auto p : game->playerList) {
				p->setReinforcement(50);
				p->set_all_territories(allTerritories);
				p->gethandofcard()->add_CardinHand(game->deck->draw());
			}

			//Add players and get continents and territories
			vector<Continent*> continents = game->map->getAllContinents();
			// vector to record the winners
			vector<string> winners;

			int turn = 1;
			while (game->playerList.size() > 1 && turn <= game->maxNumberOfTurns) {

				// assign troops
				for (auto p : game->playerList) {
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
				for (auto p : game->playerList)
					p->issueOrder("deploy");

				for (auto p : game->playerList)
					if (p->getTerriotory().size() == 0)
						continue;
					else
						p->issueOrder("advance");

				for (auto p : game->playerList)
					if (p->getTerriotory().empty())
						game->playerList.erase(find(game->playerList.begin(), game->playerList.end(), p));
				turn += 1;
			}
			if (game->playerList.size() == 1)
			{
				cout << "The game has ended, the winner is  " << game->playerList[0]->getName() << endl;
				winners.push_back(game->playerList[0]->getName());
			}
			else
			{
				cout << "The game has ended as a draw" << endl;
				winners.push_back("Draw");
			}
		}
	}
}