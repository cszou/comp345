#include "PlayerStrategiesDriver.h"
#include "GameEngineDriver.h"
#include "GameEngine.h"
#include "Player.h"
#include "PlayerStrategies.h"
#include <iostream>
using std::cin;
using std::cout;
#include <string>
using std::string;
#include <vector>
using std::vector;

void testPlayerStrategies()
{
    GameEngine *game = new GameEngine();
    game->startupFinished = true;
    game->readMap("europe.map");
    vector<Territory *> allTerritories = game->map->getAllTerritories();
    // Add new players
    Player *human = new Player("Human", game);
    Player *Cheater = new Player("Cheater", game);
    Player *Aggressive = new Player("Aggressive", game);
    Player *Benevolent = new Player("Benevolent", game);
    Player *Neutral = new Player("Neutral", game);
    // Set player strategy
    human->setPlayerStrategy(new HumanPlayerStrategy(human));
    Cheater->setPlayerStrategy(new CheaterPlayerStrategy(Cheater));
    Benevolent->setPlayerStrategy(new BenevolentPlayerStrategy(Benevolent));
    Aggressive->setPlayerStrategy(new AggressivePlayerStrategy(Aggressive));
    Neutral->setPlayerStrategy(new NeutralPlayerStrategy(Neutral));
    game->playersList.push_back(human);
    game->playersList.push_back(Cheater);
    game->playersList.push_back(Neutral);
    
    // Distribute territories to players
    int size = allTerritories.size() / 2;
    for (int i = 0; i < 2; i++){
         for (int k = 0; k < size; k++)
         {
        Territory *t = allTerritories.back();
        game->playersList[i]->addTerritory(t);
        t->setOwner(game->playersList[i]);
        allTerritories.pop_back();
        }
        }
        cout<<"here"<<endl;
    // Distribute army to Terriotories
    // set Reinforcement pool to each player
    game->playersList[0]->setReinforcement(50);
    game->playersList[1]->setReinforcement(50);
    game->playersList[2]->setReinforcement(50);
    for (int i = 0; i < 2; i++)
    {
        for (Territory *t : game->playersList[i]->getTerriotory())
        {
            t->setNumberOfArmies(game->playersList[i]->getReinforcement() / game->playersList[i]->getTerriotory().size());
        }
    }
    cout<< "--------------Testing Human player & Cheater player--------------"<<endl;
    // Excecute order
    cout <<"Human start with "<< game->playersList[0]->getTerriotory().size() << endl;
    cout <<"Cheater start with "<< game->playersList[1]->getTerriotory().size() << endl;
    string order;
    while (order != "yes")
    {
        cout << "Choose following order: " << endl;
        cout << "-Deploy\n-bomb\n-Advance\n-airlift\n-blockade " << endl;
        cin >> order;
        game->playersList[0]->issueOrder(order);
        game->playersList[1]->issueOrder("cheat");
        cout << "\nAre you done with issuing order? (yes/no) " << endl;
        cin >> order;
    }
    cout << "After play with Cheater, Human has: " << game->playersList[0]->getTerriotory().size() << endl;
    cout << "After cheating,Cheter has: " << game->playersList[1]->getTerriotory().size() << endl;

    cout<< "--------------Testing Human player & Neutral player--------------"<<endl;
    int t = game->playersList[1]->getTerriotory().size()/2;
    //Add territory back to human for testing
    for (int k = 0; k < t; k++)
         {
        Territory *t = game->playersList[1]->getTerriotory().back();
        game->playersList[0]->addTerritory(t);
        t->setOwner(game->playersList[0]);
         game->playersList[1]->deleteTerriotory(game->playersList[1]->getTerriotory().back());
        }
    //Distribute territory to Neutral player
     for (int k = 0; k < t; k++)
         {
        Territory *t = game->playersList[1]->getTerriotory().back();
        game->playersList[2]->addTerritory(t);
        t->setOwner(game->playersList[2]);
        game->playersList[1]->deleteTerriotory(game->playersList[1]->getTerriotory().back());
        }

    cout<<"Neutral's territorries are :"<<endl;
     for (Territory *t: Neutral->getTerriotory()){
            cout<< t->getName()<<" ";
     }
     cout<<"\n---------------------------------------------"<<endl;
    for (Territory *t : game->playersList[2]->getTerriotory())
        {
            t->setNumberOfArmies(game->playersList[2]->getReinforcement() / game->playersList[2]->getTerriotory().size());
        }
    string order2;
    while (order2 != "yes")
    {
        cout << "Choose following order: " << endl;
        cout << "-Deploy\n-bomb\n-Advance\n-airlift\n-blockade " << endl;
        cin >> order2;
        game->playersList[0]->issueOrder(order);
        if(order2 == "bomb"||order2 == "Advance"){
               Neutral->setifattected();
        }
        game->playersList[2]->issueOrder("Advance");
        cout << "\nAre you done with issuing order? (yes/no) " << endl;
        cin>>order2;
    }


    cout<< "--------------Testing Aggressive player & Benevolent player--------------"<<endl;
        GameEngine *game2 = new GameEngine();
        game2->startupFinished = true;
        game2->readMap("europe.map");
        vector<Territory *> allTerritories3 = game2->map->getAllTerritories();
        game2->playersList.push_back(Aggressive);
        game2->playersList.push_back(Benevolent);
        Aggressive->setReinforcement(100);
        Benevolent->setReinforcement(100);
        //Set armies
        for (int i = 0; i < game2->playersList.size(); i++)
        {
          for (Territory *t : game2->playersList[i]->getTerriotory())
         {
            t->setNumberOfArmies(game2->playersList[i]->getReinforcement() / game->playersList[i]->getTerriotory().size());
         }
         }
        size = allTerritories3.size() / 2;
         for (int i = 0; i < game2->playersList.size(); i++){
         for (int k = 0; k < size; k++)
         {
        Territory *t = allTerritories3.back();
        game2->playersList[i]->addTerritory(t);
        t->setOwner(game->playersList[i]);
        allTerritories3.pop_back();
        }
        }
      cout << "----------------------Deploy for Aggressive----------------------" << endl;
      game2->playersList[0]->issueOrder("Deploy");
      cout << "----------------------Advance for Aggressive----------------------" << endl;
      game2->playersList[0]->issueOrder("Advance");
     
      cout << "----------------------Deploy for Benevolent----------------------" << endl;
      game2->playersList[1]->issueOrder("Deploy");
      cout << "----------------------Advance for Benevolent----------------------" << endl;
      game2->playersList[1]->issueOrder("Advance");

}