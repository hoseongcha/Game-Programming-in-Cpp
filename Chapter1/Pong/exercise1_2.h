#pragma once

#define SDL_MAIN_HANDLED
#include "SDL/SDL.h"

#include <vector>

struct Vector2
{
	float x;
	float y;
};

class Game
{
public:
	explicit Game(size_t ballCount);

	bool startup();
	void shutdown();

	void runLoop();

private:
	void processInput();
	void updateGame();
	void generateOutput();

private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	Vector2 paddlePosition_;
	int paddleDirection_;

	std::vector<Vector2> ballPositions_;
	std::vector<Vector2> ballVelocities_;

	Uint32 ticksCount_;

	bool isRunning_;
};