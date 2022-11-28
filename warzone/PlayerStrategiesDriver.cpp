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
void testPlayerStrategies(){

    

    //Add new players
    Player* human = new Player("Human");
    Player* Neutral = new Player("Neutral");
    Player* Cheater = new Player("Cheater");
    //Player* Aggressive = new Player("Aggressive");
    //Player* Benevolent = new Player("Benevolent");

    //Set player strategy
    human->setPlayerStrategy(new HumanPlayerStrategy(human));
    Neutral->setPlayerStrategy(new NeutralPlayerStrategy(Neutral));
    Cheater->setPlayerStrategy(new CheaterPlayerStrategy(Cheater));
    //Aggressive->setPlayerStrategy(new AggressivePlayerStrategy(Aggressive));
    //Benevolent->setPlayerStrategy(new AggressivePlayerStrategy(Aggressive));



}
