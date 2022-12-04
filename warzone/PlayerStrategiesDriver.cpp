#include "PlayerStrategiesDriver.h"
#include "GameEngine.h"
#include "Player.h"
#include "Card.h"
#include "PlayerStrategies.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include "GameEngineDriver.h"
#include <map>
using namespace std;

void testPlayerStrategies(){

    
    GameEngine* game = new GameEngine();
	game->startupFinished = true;
	game->readMap("europe.map");
    vector<Territory*> allTerritories = game->map->getAllTerritories();
    vector<Continent*> continents = game->map->getAllContinents();

    //Add new players
    Player* human = new Player("Human",game);
   // Player* Neutral = new Player("Neutral".game);
    Player* Cheater = new Player("Cheater",game);
    //Player* Aggressive = new Player("Aggressive",game);
    //Player* Benevolent = new Player("Benevolent",game);

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
    cout<< "--------------Testing Human player & Neutral player--------------"<<endl;
     cout<< "Human has terriotories: "<<game->playersList[0]->getTerriotory().size()<<endl;
     cout<< "Cheter has terriotories: "<<game->playersList[1]->getTerriotory().size()<<endl;

    //set Reinforcement pool to each player
    game->playersList[0]->setReinforcement(50);
    game->playersList[1]->setReinforcement(50);
    //Distribute army to Terriotories
    for(int i =0; i<game->playersList.size();i++){
    for(Territory* t:game->playersList[i]->getTerriotory()){
        t->setNumberOfArmies(game->playersList[i]->getReinforcement()/game->playersList[i]->getTerriotory().size());
    }
    }
    //game->playersList[0]->set_players_Map(game->playersList);
    //Excecute order 
    string order;
    while (order!="yes"){
    cout <<"Choose following order: "<<endl;
	cout <<"-Deploy\n-bomb\n-Advance\n-airlift\n-blockade "<<endl;
	cin>>order;
    game->playersList[0]->issueOrder(order);
    game->playersList[1]->issueOrder("cheat");
    cout <<"\nAre you done with issuing order? (yes/no) "<<endl;
    }
    cout<< "After play with Cheater, Human has: "<<game->playersList[0]->getTerriotory().size()<<endl;
    cout<< "After cheating,Cheter has: "<<game->playersList[1]->getTerriotory().size()<<endl;
}
//int main(){
  //  testPlayerStrategies();
//}
