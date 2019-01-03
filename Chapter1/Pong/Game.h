#pragma once

#define SDL_MAIN_HANDLED
#include "SDL/SDL.h"

class Game
{
public:
	Game();

	bool startup();
	void shutdown();

	void run_loop();

private:
	void process_input();
	void update_game();
	void generate_output();

private:
	SDL_Window* window_;
	bool isRunning_;
};