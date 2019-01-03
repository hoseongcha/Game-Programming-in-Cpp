#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	bool success = game.startup();

	if (success)
		game.run_loop();
	game.shutdown();

	return 0;
}