#include "GameEngine.h"
#include "CommandProcessing.h"

void testCommandProcessor() {
	string cont = "y";
	while(cont=="y")
	{
		GameEngine* game = new GameEngine();
		cout << "Where do you want to read commands from? 1. console / 2. file: ";
		string ans;
		cin >> ans;
		if (ans == "1" || ans == "console")
			// read from console
		{
			cout << "********************read commands from console********************" << endl;
			CommandProcessor* cp = new CommandProcessor(game);
			for (int i = 0;i < 5;i++)
			{
				Command* c1 = cp->getCommand();
				cp->validate(c1);
			}
			delete cp;
			delete game;
		}
		else if (ans == "2"|| ans == "file")
			// read from file
		{
			GameEngine* game = new GameEngine();
			Command* temp = new Command();
			cout << "********************read commands from console********************" << endl;
			CommandProcessor* fcp = new FileCommandProcessorAdapter(game);
			while (temp->getCommandString() != "eof") {
				temp = fcp->getCommand();
				fcp->validate(temp);
			}
			delete fcp;
			delete game;
		}
		else
			cout << "Wrong selection.";
		cout << "do you want to try again? y/n: ";
		cin >> cont;
	}
}