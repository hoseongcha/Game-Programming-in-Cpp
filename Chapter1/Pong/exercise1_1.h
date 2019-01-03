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

	void runLoop();

private:
	void processInput();
	void updateGame();
	void generateOutput();

private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	Vector2 leftPaddlePosition_;
	Vector2 rightPaddlePosition_;

	int leftPaddleDirection_;
	int rightPaddleDirection_;

	Vector2 ballPosition_;
	Vector2 ballVelocity_;

	Uint32 ticksCount_;
	
	bool isRunning_;
};