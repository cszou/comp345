#include "MapDriver.h"
#include "PlayerDriver.h"
#include "OrdersDriver.h"
#include "CardsDriver.h"
#include "GameEngineDriver.h"
#include "CommandProcessingDriver.h"
#include "LoggingObserverDriver.h"


int main() {
	//testLoadMaps();
	//testPlayers();
	//testOrdersLists();
	//testCards();
	//testGameStates();
	testCommandProcessor();
	//testStartPhase();
	//testMainGameLoop();
	//testOrderExecution();
	testLoggingObserver();
}
