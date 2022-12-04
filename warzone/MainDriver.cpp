#include "MapDriver.h"
#include "PlayerDriver.h"
#include "OrdersDriver.h"
#include "GameEngineDriver.h"
#include "CommandProcessingDriver.h"
#include "LoggingObserverDriver.h"
#include "TournamentDriver.h"
#include "PlayerStrategiesDriver.h"
#include <iostream>
using std::cout;
using std::endl;


int main() {
	//cout << endl << "************* Part 1 *************" << endl;
	//testCommandProcessor();
	//cout << endl << "************* Part 2 *************" << endl;
	//testStartupPhase();
	//cout << endl << "************* Part 3 *************" << endl;
	//testMainGameLoop();
	//cout << endl << "************* Part 4 *************" << endl;
	//testOrderExecution();
	//cout << endl << "************* Part 5 *************" << endl;
	//testLoggingObserver();
	//testPlayerStrategies();
	testTournament();
}
