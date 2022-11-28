#include "TournamentDriver.h"
#include "GameEngine.h"
#include "CommandProcessing.h"

void testTournament()
{
	GameEngine* game = new GameEngine();
	cout << "Please enter a tournament command:\n";
	CommandProcessor* cp = new CommandProcessor(game);
	cp->getCommand();
}
