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
	
    //Testing the GameEngine
    engine->setState("Start");
    engine->setState("Map Loaded");
    engine->setState("Assign Reinforcement");
    engine->setState("Win");	

    //Testing the CommandProcessor
    //Testing the Order 
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
