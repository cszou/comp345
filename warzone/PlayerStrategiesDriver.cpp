#include "PlayerStrategiesDriver.h"
#include "GameEngineDriver.h"
#include "GameEngine.h"
#include "Player.h"

#include <iostream>
using std::cin;
using std::cout;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include "GameEngineDriver.h"

void testPlayerStrategies(){

    
    GameEngine* game = new GameEngine();
	game->startupFinished = true;
	game->readMap("europe.map");
    vector<Territory*> allTerritories = game->map->getAllTerritories();

    //Add new players
    Player* human = new Player("Human");
   // Player* Neutral = new Player("Neutral");
    Player* Cheater = new Player("Cheater");
    //Player* Aggressive = new Player("Aggressive");
    //Player* Benevolent = new Player("Benevolent");

    //Set player strategy
    human->setPlayerStrategy(new HumanPlayerStrategy(human));
    //Neutral->setPlayerStrategy(new NeutralPlayerStrategy(Neutral));
    Cheater->setPlayerStrategy(new CheaterPlayerStrategy(Cheater));
    //Aggressive->setPlayerStrategy(new AggressivePlayerStrategy(Aggressive));
    //Benevolent->setPlayerStrategy(new AggressivePlayerStrategy(Aggressive));
    game->playersList.push_back(human);
	game->playersList.push_back(Cheater);
    //Distribute territories to players
    int size = allTerritories.size()/2;
	//while (!allTerritories.empty()) {
		for (int i = 0; i < size; i++) {
			Territory* t = allTerritories.back();
			game->playersList[0]->addTerritory(t);
			t->setOwner(game->playersList[0]);
			allTerritories.pop_back();
		}
        for (int i = 0; i < size; i++) {
			Territory* t = allTerritories.back();
			game->playersList[1]->addTerritory(t);
			t->setOwner(game->playersList[1]);
			allTerritories.pop_back();
		}
	//}


    cout<< "--------------Testing Human player & Neutral player--------------"<<endl;
     cout<< "Human has: "<<game->playersList[0]->getTerriotory().size()<<endl;
     cout<< "Cheter has: "<<game->playersList[1]->getTerriotory().size()<<endl;
    game->playersList[0]->issueOrder("Deploy");
    game->playersList[1]->issueOrder("Advance");
    
    cout<< "After play with Cheater, Human has: "<<game->playersList[0]->getTerriotory().size()<<endl;
    cout<< "After cheating,Cheter has: "<<game->playersList[1]->getTerriotory().size()<<endl;
    //game->playersList[1]->issueOrder("Deploy");
    //game->playersList[1]->issueOrder("Deploy");


}
//int main(){
   // testPlayerStrategies();
//}
