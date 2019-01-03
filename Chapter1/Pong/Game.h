#pragma once

#define SDL_MAIN_HANDLED
#include "SDL/SDL.h"

struct Vector2
{
	float x;
	float y;
};

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
	SDL_Renderer* renderer_;

	Vector2 paddlePosition_;
	Vector2 ballPosition_;

	bool isRunning_;
};