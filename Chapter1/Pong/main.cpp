#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	bool success = game.startup();

	if (success)
		game.runLoop();
	game.shutdown();

	return 0;
}