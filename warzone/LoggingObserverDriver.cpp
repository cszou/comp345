#include <iostream>
#include "LoggingObserver.h"
#include "Map.h"
#include "Player.h"
#include "CommandProcessing.h"
#include "GameEngine.h"
#include "Orders.h"
#include "Card.h"
using namespace std;

void testLoggingObserver(){
    //Create a log observer object
    LogObserver *ob = new LogObserver();
//--------------------------GameEngine------------------------------------------
    //Create Gameengine object and change it state, so the Notify method will be invoked
    GameEngine* engine = new GameEngine();
    engine -> Attach(ob);
    //Testing the GameEngine, when game engine change its state, the new state will be written to the log file
    cout<<"Changing Game engine's state, updated string will be updated to file "<<endl;
    engine->setState("Start");
    engine->setState("Map Loaded");
    engine->setState("Assign Reinforcement");
    engine->setState("Win");

//-----------------------CommandProcessor&Command---------------------------------------------
    //Create CommandProcessor objects for testing
    GameEngine *game  = new GameEngine();
    game->setState("Win");
	// read from console
	CommandProcessor* cp = new CommandProcessor(game);
    cp -> Attach(ob);
	Command* c1 = cp->getCommand();
    c1 -> Attach(ob);
    c1->saveEffect();
	cp->validate(c1);
	// read from file
	CommandProcessor* fcp = new FileCommandProcessorAdapter(game);
    fcp->Attach(ob);
	Command* c2 = fcp->getCommand();
    c2 ->Attach(ob);
    c2->saveEffect();
   
	fcp->validate(c2);
	Command* c3 = fcp->getCommand();
    c3->Attach(ob);
    c3->saveEffect();
	fcp->validate(c3);
//--------------------Order&OrderList------------------------------------------------
     int NUMBEROFARMY = 10; // add army
    Territory *A1 = new Territory("A1");
    int ownarmy = 150;
    int targetarmy = 200;
    A1->setNumberOfArmies(targetarmy);
    Territory *A2 = new Territory("A2");
    A2->setNumberOfArmies(ownarmy);
    OrderList *OL1 = new OrderList();
    OL1->Attach(ob);
    OrderList *OL2 = new OrderList();
     OL2->Attach(ob);
    vector<Territory *> T1;
    T1.push_back(A2);
    vector<Territory *> T2;
    T2.push_back(A1);
    Hand *H = new Hand();
    Player *P1 = new Player(T1, H, "P1", OL1);
    Player *P2 = new Player(T2, H, "P2", OL2);
   
    A2->setOwner(P1);
    A1->setOwner(P2);

    Deploy *deploy = new Deploy(NUMBEROFARMY, P1, A2);
    Advance *advance = new Advance(A2, A1, P1, NUMBEROFARMY);
    Airlift *airlift = new Airlift(P1, A1, A2);
    Bomb *bomb = new Bomb(P1, A1, &NUMBEROFARMY);
    deploy -> Attach(ob);
    airlift -> Attach(ob);
    advance -> Attach(ob);
    bomb -> Attach(ob);

    deploy -> execute();
    airlift->execute();
    bomb->execute();
    advance->execute();

    OL1->add(deploy);
    OL1->add(airlift);
    OL1->add(bomb);
    OL1->add(advance);

  //Deleting pointers to prevent memory leak 
    delete ob;
    delete engine; 
    delete game; delete cp; delete fcp;
    delete P1;
    delete P2;
}
