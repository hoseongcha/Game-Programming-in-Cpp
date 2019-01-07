#pragma once

#define SDL_MAIN_HANDLED
#include "SDL/SDL.h"

#include <vector>

class Game
{
public:
	Game();

	bool startup();
	void shutdown();

	void runLoop();

	void addActor(class Actor* actor);
	void removeActor(class Actor* actor);

private:
	void loadData();
	void unloadData();

	void processInput();
	void updateGame();
	void generateOutput();

private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	Uint32 ticksCount_;

	std::vector<class Actor*> actors_;
	std::vector<class Actor*> pendingActors_;

	bool isRunning_;
	bool updatingActors_;
};