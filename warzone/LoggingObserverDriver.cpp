#include "LoggingObserver.h"
#include "LoggingObserverDriver.h"
#include "CommandProcessing.h"
#include "GameEngine.h"
#include "Orders.h"
using namespace std;

void testLoggingObserver(){
    //Create a log observer object
    LoggingObserver *ob = new LoggingObserver();
	
    //Create ILoggable objects for testing
    CommandProcessor* commandprocessor = new CommandProcessor();
    Command command = new  Command();	
    GameEngine* engine = new GameEngine();
	
    //Attach each object to the observer object
    commandprocessor -> attach(ob);
    engine -> attach(ob);
    command  -> attach(ob);
	
    //Testing the GameEngine, when game engine change its state, the new state will be written to the log file
    engine->setState("Start");
    engine->setState("Map Loaded");
    engine->setState("Assign Reinforcement");
    engine->setState("Win");	

    //Testing the CommandProcessor, when a command is read, it is written in the log file
    //Testing the Order 
	
    // create  Territory object
    Territory* A1= new Territory("A1");
    Territory* A2= new Territory("A2");
    Hand* h = new Hand();
    Deck *d = new Deck();
    Player* K =new Player({A2,A1},h,"Player1");
	
    //create each order objects
    Order* deploy = new Deploy(&NUMBEROFARMY,K,F);
    Order* advance= new Advance();
    Order* airlift= new Airlift(); 
    Order* bomb = new Bomb (); 
    Order* blockade= new Blockade(); 
    Order* negotiate= new Negotiate();
    //Attach each object to the observer object
    deploy -> attach(ob);
    advance -> attach(ob);
    airlift -> attach(ob);
    bomb -> attach(ob);
    blockade -> attach(ob);
    negotiate -> attach(ob);
	
    //Testing Order execute method, the exceuted order will be outputed to log file
    deploy->execute();
    advance->execute();
    airlift->execute();
    bomb->execute();
    blockade->execute();
    negotiate->execute();

    //create orderlist object and attach it to the observer object 
    OrderList* testOrderList =new OrderList();
    testOrderList -> attach(ob);
    //Testing orderlist addOrder, the added order will be outputed to log file
    testOrderList -> add(deploy);
    testOrderList -> add(advance);
    testOrderList -> add(airlift);
    testOrderList -> add(bomb);
    testOrderList -> add(blockade); 
    testOrderList -> add(negotiate);
	
  //Deleting pointers to prevent memory leak 
    delete ob;
    delete commandprocessor;
    delete engine; 
    delete A1, A2;
    delete deploy, advance, airlift, bomb, blockade, negotiate;
	
}

/*
Method implement in Iloggable classes

string Orders :: stringToLog(){
    return "Order Excecuted: "<< ;
}
string OrderList :: stringToLog(){
    string OrderList = "Order Issued: "
    return OrderList;
}
string GameEngine::stringToLog() {
    string GameEngine = "Game Engine New State: " + getState();
    return GameEngine
}
string CommandProcessor::stringToLog(){
	return "Command: " + commandList.back()->getCommandStr() + " into the list.";
}

string Command::stringToLog() {
	string command = "Command issued: " + getCommandStr()
		+ "\nCommand's effect: " + getEffect();
	return "Command issued: "<< getEffect();
}

*/
