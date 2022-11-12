#include "GameEngine.h"
#include "CommandProcessing.h"

void testCommandProcessor() {
	GameEngine *game  = new GameEngine();
	// read from console;
	CommandProcessor *cp = new CommandProcessor(game);
	Command* c1 = cp->getCommand();
}