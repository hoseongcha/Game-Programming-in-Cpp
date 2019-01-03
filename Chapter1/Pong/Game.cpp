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
		"Game Programming in C++ (Chapter 1)",	// 타이틀
		100,	// x 좌표
		100,	// y 좌표
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
		window_,	// 렌더러를 생성할 윈도우 포인터
		-1,			// graphics driver (보통은 -1)
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC	// 하드웨어 가속, 수직 동기화
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
	// 초기화 했던 반대 순서로 종료한다.

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

	// 이벤트 큐에 이벤트가 들어있으면 처리한다.
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
	// 1. back buffer를 초기화
	SDL_SetRenderDrawColor(renderer_, 0, 0, 255, 255);
	SDL_RenderClear(renderer_);

	// 2. 게임을 그린다.

	// 3. front buffer와 back buffer를 교환.
	SDL_RenderPresent(renderer_);
}
