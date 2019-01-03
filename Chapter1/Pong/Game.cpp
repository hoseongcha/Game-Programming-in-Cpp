#include "Game.h"

Game::Game()
	: window_(nullptr), isRunning_(true)
{
}

bool Game::startup()
{
	SDL_SetMainReady();

	int result = SDL_Init(SDL_INIT_VIDEO);
	if (result != 0)
	{
		SDL_Log("Unable to initialize SDL : %s", SDL_GetError());
		return false;
	}

	window_ = SDL_CreateWindow("Game Programming in C++ (Chapter 1)",
		100,
		100,
		1024,
		768,
		0);
	if (!window_)
	{
		SDL_Log("Failed to create window : %s", SDL_GetError());
		return false;
	}

	return true;
}

void Game::shutdown()
{
	// 초기화 했던 반대 순서로 종료한다.

	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Game::run_loop()
{
	while (isRunning_)
	{
		process_input();
		update_game();
		generate_output();
	}
}

void Game::process_input()
{
}

void Game::update_game()
{
}

void Game::generate_output()
{
}
