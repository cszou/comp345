#include "MapDriver.h"
#include "PlayerDriver.h"
#include "OrdersDriver.h"
#include "GameEngineDriver.h"
#include "CommandProcessingDriver.h"
#include "LoggingObserverDriver.h"


int main() {
	testCommandProcessor();
	//testStartPhase();
	//testMainGameLoop();
	testOrderExecution();
	//testLoggingObserver();
}
