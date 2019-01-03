// #include "Game.h"
// #include "exercise1_1.h"
#include "exercise1_2.h"

int main(int argc, char** argv)
{
	// Game game;
	Game game(2);
	bool success = game.startup();

	if (success)
		game.runLoop();
	game.shutdown();

	return 0;
}