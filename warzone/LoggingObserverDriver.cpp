#include <iostream>
#include "LoggingObserver.h"
#include "Map.h"
#include "Player.h"
#include "CommandProcessing.h"
#include "GameEngine.h"
#include "Orders.h"
#include "Card.h"
//#include "loggableObject.h"
using namespace std;

void testLoggingObserver(){
cout<<"----------------------Part 5 Driver----------------------------------------------"<<endl;
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
}
   
//--------------------Order&OrderList------------------------------------------------
/*
    // create  Territory object
    int NUMBEROFARMY =13;
    Territory* A1= new Territory("A1");
    Territory* A2= new Territory("A2");
    Territory* A3= new Territory("A3");
    Territory* A4= new Territory("A4");
    vector<Territory*> t1;
    t1.push_back(A1);
	t1.push_back(A2);
    vector<Territory*> t2;
    t2.push_back(A3);
	t2.push_back(A4);
    Hand* h = new Hand();
    Deck *d = new Deck();
    OrderList* o1 =new OrderList();
    OrderList* o2 =new OrderList();
    Player* P1 =new Player(t1,h,"Player1",o1);
    Player* P2 =new Player(t2,h,"Player2",o2);
	
    //create each order objects
    Deploy* deploy = new Deploy(&NUMBEROFARMY,P1,A1);
    Advance* advance= new Advance(A1,A2,P1,&NUMBEROFARMY);
   // Airlift* airlift= new Airlift(P1, A1,A2); 
    Bomb* bomb = new Bomb (P1, A1,&NUMBEROFARMY); 
    Blockade* blockade= new Blockade(P1,A1); 
    //Order* negotiate= new Negotiate(P1,P2);

    //Attach each object to the observer object
    deploy -> Attach(ob);
    advance -> Attach(ob);
    //airlift -> Attach(ob);
    bomb -> Attach(ob);
    blockade -> Attach(ob);
    //negotiate -> Attach(ob);
	
    //Testing Order execute method, the exceuted order will be outputed to log file
    deploy->execute();
    advance->execute();
    //airlift->execute();
    bomb->execute();
    blockade->execute();
    //negotiate->execute();

    //create orderlist object and attach it to the observer object 
    OrderList* testOrderList =new OrderList();
    testOrderList -> Attach(ob);
    //Testing orderlist addOrder, the added order will be outputed to log file
    testOrderList -> addOrders(deploy);
    testOrderList -> addOrders(advance);
    //testOrderList -> addOrders(airlift);
    testOrderList -> addOrders(bomb);
    testOrderList -> addOrders(blockade); 
    //testOrderList -> add(negotiate);
//--------------------------Deleting Pointers------------------------------------------
  //Deleting pointers to prevent memory leak 
   // delete ob;
   // delete engine; 
   // delete game; delete cp; delete fcp;
   
   
   // delete A1, A2;
   // delete deploy, advance, airlift, bomb, blockade ;//negotiate;
	
}*/
