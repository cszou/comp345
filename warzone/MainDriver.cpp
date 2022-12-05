#include "TournamentDriver.h"
#include "PlayerStrategiesDriver.h"
#include <iostream>
using std::cout;
using std::endl;


int main() {
	cout << "\n************* Part 1: Player Strategy *************" << endl;
	testPlayerStrategies();
	cout << "\n************* Part 2: Tournament Mode *************" << endl;
	testTournament();
}
