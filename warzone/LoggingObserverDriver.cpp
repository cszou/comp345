#include <iostream>
#include "LoggingObserver.h"
#include "Map.h"
#include "Player.h"
#include "LoggingObserverDriver.h"
#include "CommandProcessing.h"
#include "GameEngine.h"
#include "Orders.h"
#include "Card.h"
//using namespace std;

void testLoggingObserver(){
    //Create a log observer object
    LogObserver *ob = new LogObserver();
	/*
    //Create ILoggable objects for testing
    CommandProcessor* commandprocessor = new CommandProcessor();
   // Command command = new  Command();	
    GameEngine* engine = new GameEngine();
	
    //Attach each object to the observer object
    commandprocessor -> Attach(ob);
    engine -> Attach(ob);
    //command  -> Attach(ob);
	
    //Testing the GameEngine, when game engine change its state, the new state will be written to the log file
    engine->setState("Start");
    engine->setState("Map Loaded");
    engine->setState("Assign Reinforcement");
    engine->setState("Win");	
    */
    //Testing the CommandProcessor, when a command is read, it is written in the log file
    //Testing the Order 
	
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
    Airlift* airlift= new Airlift(P1, A1,A2); 
    Bomb* bomb = new Bomb (P1, A1,&NUMBEROFARMY); 
    Blockade* blockade= new Blockade(P1,A1); 
    //Order* negotiate= new Negotiate(P1,P2);

    //Attach each object to the observer object
    deploy -> Attach(ob);
    advance -> Attach(ob);
    airlift -> Attach(ob);
    bomb -> Attach(ob);
    blockade -> Attach(ob);
    //negotiate -> Attach(ob);
	
    //Testing Order execute method, the exceuted order will be outputed to log file
    deploy->execute();
    advance->execute();
    airlift->execute();
    bomb->execute();
    blockade->execute();
    //negotiate->execute();

    //create orderlist object and attach it to the observer object 
    OrderList* testOrderList =new OrderList();
    testOrderList -> Attach(ob);
    //Testing orderlist addOrder, the added order will be outputed to log file
    testOrderList -> addOrders(deploy);
    testOrderList -> addOrders(advance);
    testOrderList -> addOrders(airlift);
    testOrderList -> addOrders(bomb);
    testOrderList -> addOrders(blockade); 
    //testOrderList -> add(negotiate);
	
  //Deleting pointers to prevent memory leak 
   // delete ob;
    //delete commandprocessor;
   // delete engine; 
   // delete A1, A2;
   // delete deploy, advance, airlift, bomb, blockade ;//negotiate;
	
}
/*
int main(){
    void testLoggingObserver();
}



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
