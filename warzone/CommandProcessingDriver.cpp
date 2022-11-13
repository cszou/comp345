#include "GameEngine.h"
#include "CommandProcessing.h"

void testCommandProcessor() {
	GameEngine *game  = new GameEngine();
	// read from console
	CommandProcessor* cp = new CommandProcessor(game);
	Command* c1 = cp->getCommand();
	cp->validate(c1);
	// read from file
	CommandProcessor* fcp = new FileCommandProcessorAdapter(game);
	Command* c2 = fcp->getCommand();
	fcp->validate(c2);
	Command* c3 = fcp->getCommand();
	fcp->validate(c3);
	delete cp;
	delete fcp;
}