#include "TournamentDriver.h"
#include "GameEngine.h"
#include "CommandProcessing.h"

void testTournament()
{
	char ans = 'y';
	while(ans == 'y')
	{
		GameEngine* game = new GameEngine();
		cout << "Please enter a tournament command:\n";
		CommandProcessor* cp = new CommandProcessor(game);
		cp->getCommand();
		cout << "try again? (y/n): ";
		cin >> ans;
	}
}
