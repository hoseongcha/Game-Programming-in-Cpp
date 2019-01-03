#include "Game.h"

Game::Game()
	: window_(nullptr), renderer_(nullptr),
	isRunning_(true)
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

	window_ = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)",	// Ÿ��Ʋ
		100,	// x ��ǥ
		100,	// y ��ǥ
		1024,	// width
		768,	// height
		0		// flags
	);
	if (!window_)
	{
		SDL_Log("Failed to create window : %s", SDL_GetError());
		return false;
	}
	
	renderer_ = SDL_CreateRenderer(
		window_,	// �������� ������ ������ ������
		-1,			// graphics driver (������ -1)
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC	// �ϵ���� ����, ���� ����ȭ
	);
	if (!renderer_)
	{
		SDL_Log("Failed to create renderer : %s", SDL_GetError());
		return false;
	}

	return true;
}

void Game::shutdown()
{
	// �ʱ�ȭ �ߴ� �ݴ� ������ �����Ѵ�.

	SDL_DestroyRenderer(renderer_);
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
	SDL_Event event;

	// �̺�Ʈ ť�� �̺�Ʈ�� ��������� ó���Ѵ�.
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning_ = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_ESCAPE])
		isRunning_ = false;
}

void Game::update_game()
{
}

void Game::generate_output()
{
	// 1. back buffer�� �ʱ�ȭ
	SDL_SetRenderDrawColor(renderer_, 0, 0, 255, 255);
	SDL_RenderClear(renderer_);

	// 2. ������ �׸���.

	// 3. front buffer�� back buffer�� ��ȯ.
	SDL_RenderPresent(renderer_);
}
