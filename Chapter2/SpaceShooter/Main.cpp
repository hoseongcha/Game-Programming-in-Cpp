#include "Game.h"

int main(int argc, char** argv)
{
	SDL_SetMainReady();

	Game game;
	bool success = game.startup();

	if (success)
		game.runLoop();

	game.shutdown();

	return 0;
}