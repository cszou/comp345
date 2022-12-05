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

void testPlayerStrategies()
{
    GameEngine *game = new GameEngine();
    game->startupFinished = true;
    game->readMap("europe.map");
    vector<Territory *> allTerritories = game->map->getAllTerritories();
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%creates Aggressive%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    // Add new players
    Player *human = new Player("Human", game);
    Player *Cheater = new Player("Cheater", game);
    // Set player strategy
    //human->setPlayerStrategy(new HumanPlayerStrategy(human));
    //Cheater->setPlayerStrategy(new CheaterPlayerStrategy(Cheater));
    game->playersList.push_back(human);
    game->playersList.push_back(Cheater);
    
    /*    Player *Aggressive = new Player("Aggressive", game);
        Player *bonavon = new Player("bonavon", game);
        Aggressive->setReinforcement(100);
        bonavon->setReinforcement(100);
        bonavon->setPlayerStrategy(new BenevolentPlayerStrategy(bonavon));
        Aggressive->setPlayerStrategy(new AggressivePlayerStrategy(Aggressive));
        game->playersList.push_back(Aggressive);
        game->playersList.push_back(bonavon);
    */
    // Distribute territories to players
    int size = allTerritories.size() / 2;
    for (int i = 0; i < size; i++)
    {
        Territory *t = allTerritories.back();
        game->playersList[0]->addTerritory(t);
        t->setOwner(game->playersList[0]);
        allTerritories.pop_back();
    }
    for (int i = 0; i < size; i++)
    {
        Territory *t = allTerritories.back();
        game->playersList[1]->addTerritory(t);
        t->setOwner(game->playersList[1]);
        allTerritories.pop_back();
    }
    // Distribute army to Terriotories
    // set Reinforcement pool to each player
    game->playersList[0]->setReinforcement(50);
    game->playersList[1]->setReinforcement(50);
    for (int i = 0; i < game->playersList.size(); i++)
    {
        for (Territory *t : game->playersList[i]->getTerriotory())
        {
            t->setNumberOfArmies(game->playersList[i]->getReinforcement() / game->playersList[i]->getTerriotory().size());
        }
    }
    cout << game->playersList[0]->getTerriotory().size() << endl;

    for (int i = 0; i < game->playersList[0]->getTerriotory().size(); i++)
    {
        cout << game->playersList[0]->getTerriotory().at(i)->getName() << " ";
    }
    cout << game->playersList[1]->getTerriotory().size() << endl;

    for (int i = 0; i < game->playersList[1]->getTerriotory().size(); i++)
    {
        cout << game->playersList[1]->getTerriotory().at(i)->getName() << " ";
    }

    // game->playersList[0]->set_players_Map(game->playersList);
    // Excecute order
    string order;
    while (order != "yes")
    {
        cout << "Choose following order: " << endl;
        cout << "-Deploy\n-bomb\n-Advance\n-airlift\n-blockade " << endl;
        cin >> order;
        game->playersList[0]->issueOrder(order);
        game->playersList[1]->issueOrder("cheat");
        cout << "\nAre you done with issuing order? (yes/no) " << endl;
    }
    cout << "After play with Cheater, Human has: " << game->playersList[0]->getTerriotory().size() << endl;
    cout << "After cheating,Cheter has: " << game->playersList[1]->getTerriotory().size() << endl;
    /*
      cout << "----------------------Deploy for Aggressive----------------------" << endl;
        game->playersList[1]->issueOrder("Deploy");
        cout << "----------------------Advance for Aggressive----------------------" << endl;
        game->playersList[1]->issueOrder("Advance");
        cout << "----------------------bomb for Aggressive----------------------" << endl;
        game->playersList[1]->issueOrder("bomb");
        cout << "----------------------airlift for Aggressive----------------------" << endl;
        game->playersList[1]->issueOrder("airlift");
      cout << "----------------------diplomacy for Aggressive----------------------" << endl;
      game->playersList[1]->issueOrder("diplomacy");
      cout << "----------------------blockade for Aggressive----------------------" << endl;
      game->playersList[1]->issueOrder("blockade");*/
}
//int main()
//{
//    testPlayerStrategies();
//}
//   cout << "%%%%%%%%%%%%%%%%%%%%%%%%creates Neutral%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
// Player *Neutral = new Player("Neutral");
// Set player strategy
//   Neutral->setPlayerStrategy(new NeutralPlayerStrategy(Neutral));
//    game->playersList.push_back(Neutral);
//   game->playersList.push_back(Cheater);

// cout << "nurtral has: " << game->playersList[0]->getTerriotory().size() << endl;
//  cout << "Aggressive has: " << game->playersList[0]->getTerriotory().size() << endl;
/*   cout << "----------------------Deploy for Neutral----------------------" << endl;
   game->playersList[0]->issueOrder("Deploy");
   cout << "----------------------Advance for Neutral----------------------" << endl;
   game->playersList[0]->issueOrder("Advance");
*/
/*	vector<Territory *> bannedTerritory;
 for (int i = 0; i < Aggressive->getAttackBan().size(); i++)
 {
     vector<Territory *> each_ban_player_tero = Aggressive->getAttackBan()[i]->getTerriotory();
     for (int k = 0; k < each_ban_player_tero.size(); k++)
     {
         bannedTerritory.push_back(each_ban_player_tero.at(k)); // cannot attact not dulicate
     }
 }

 vector<Territory *> toAttack;
 for (Territory *t : Aggressive->getTerriotory())
 {
     for (Territory *a : t->getNeighbours())
     {
         if (!Aggressive->ownsTerritory(a))
         {
             toAttack.push_back(a);
         }
     }
 }
 // cout<<"---the emey has"<<toAttack.size()<<endl;
 sort(toAttack.begin(), toAttack.end());
 // for (Territory* t : toAttack) {
 toAttack.erase(unique(toAttack.begin(), toAttack.end()), toAttack.end());
 for (int i = 0; i < toAttack.size(); i++)
 {
     for (int k = 0; k < bannedTerritory.size(); k++)
     {
         if (toAttack.at(i) = bannedTerritory.at(k))
             toAttack.erase(toAttack.begin() + i);
     }
 }


 for (int i = 0; i < game->playersList[0]->toAttack().size(); i++)
 {
     Aggressive1->addTerritory(toAttack.at(i));
     game->playersList[0]->toAttack().at(i)->setOwner(Aggressive1);
 }
 for (int i = 0; i < Aggressive1->getTerriotory().size(); i++)
 {
     cout << Aggressive1->getTerriotory().at(i)->getName();
 }

     cout << "hello";



 // Distribute territories to players
 int size = allTerritories.size() / 2;
 for (int i = 0; i < size; i++)
 {
     Territory *t = allTerritories.back();
     game->playersList[0]->addTerritory(t);
     t->setOwner(game->playersList[0]);
     allTerritories.pop_back();
 }
 // set Reinforcement pool to each player
 game->playersList[0]->setReinforcement(50);
 // Distribute army to Terriotories
 for (int i = 0; i < game->playersList.size(); i++)
 {
     for (Territory *t : game->playersList[i]->getTerriotory())
     {
         t->setNumberOfArmies(game->playersList[i]->getReinforcement() / game->playersList[i]->getTerriotory().size());
     }
 }
 for (int i = 0; i < game->playersList[0]->getTerriotory().size(); i++)
 {
     cout << game->playersList[0]->getTerriotory().at(i)->getNumberOfArmies() << "hel" << endl;
 }
 //  game->playersList[0]->set_players_Map(game->playersList);
*/