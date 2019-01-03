#include "exercise1_2.h"
#include <ctime>

const int thickness = 15;
const float paddleHeight = 100;

Game::Game(size_t ballCount)
	: window_(nullptr), renderer_(nullptr),
	paddleDirection_(0),
	ballPositions_(ballCount), ballVelocities_(ballCount),
	ticksCount_(0),
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

	paddlePosition_.x = 10;
	paddlePosition_.y = 768 / 2.0f;

	srand(static_cast<unsigned int>(time(nullptr)));

	for (auto& position : ballPositions_)
	{
		float x = rand() % 1024;
		float y = rand() % 768;

		if (x < paddlePosition_.x + thickness)
			x = paddlePosition_.x + thickness + 100;
		else if (x > 1024 - thickness)
			x = 1024 - thickness - 100;

		if (y < thickness)
			y = thickness + 100;
		else if (y > 768 - thickness)
			y = 768 - thickness + 100;

		position.x = x;
		position.y = y;
	}

	for (auto& velocity : ballVelocities_)
	{
		float x = rand() % 150 + 100;
		float y = rand() % 150 + 100;
		int sign = rand() % 100;

		if (sign <= 33)
			x *= -1;
		else if (sign <= 66)
			y *= -1;

		velocity.x = x;
		velocity.y = y;
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

void Game::runLoop()
{
	while (isRunning_)
	{
		processInput();
		updateGame();
		generateOutput();
	}
}

void Game::processInput()
{
	int a = 0;

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

	paddleDirection_ = 0;
	if (state[SDL_SCANCODE_W])
		paddleDirection_ -= 1;
	if (state[SDL_SCANCODE_S])
		paddleDirection_ += 1;
}

void Game::updateGame()
{
	// ��� �ð��� ��ǥ�� ������ �ð����� �� ������, (���⼭�� ��ǥ ������ �ð��� 60FPS)
	// 60FPS�� �ɶ����� ��ٸ���.
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount_ + 16))
		;

	float deltaTime = (SDL_GetTicks() - ticksCount_) / 1000.0f;

	// ��� �ð��� ��ǥ�� ������ �ð����� �� ������,
	// ��� �ð��� 0.05f�� �����Ѵ�.
	if (deltaTime > 0.05f)
		deltaTime = 0.05f;

	ticksCount_ = SDL_GetTicks();

	if (paddleDirection_ != 0)
	{
		paddlePosition_.y += paddleDirection_ * 300.0f * deltaTime;

		if (paddlePosition_.y < (paddleHeight / 2.0f + thickness))
			paddlePosition_.y = paddleHeight / 2.0f + thickness;
		else if (paddlePosition_.y > (768.0f - paddleHeight / 2.0f - thickness))
			paddlePosition_.y = 768.0f - paddleHeight / 2.0f - thickness;
	}

	for (size_t i = 0; i < ballPositions_.size(); ++i)
	{
		ballPositions_[i].x += ballVelocities_[i].x * deltaTime;
		ballPositions_[i].y += ballVelocities_[i].y * deltaTime;

		if (ballPositions_[i].x <= 0.0f || ballPositions_[i].x >= 1024.0f)
			isRunning_ = false;

		if (ballPositions_[i].y < thickness && ballVelocities_[i].y < 0.0f)
			ballVelocities_[i].y *= -1;
		else if (ballPositions_[i].y > 768.0f - thickness && ballVelocities_[i].y > 0.0f)
			ballVelocities_[i].y *= -1;
		else if (ballPositions_[i].x > 1024.0f - thickness && ballVelocities_[i].x > 0.0f)
			ballVelocities_[i].x *= -1;

		float diff = fabs(paddlePosition_.y - ballPositions_[i].y);
		if (diff <= paddleHeight / 2.0f &&
			ballPositions_[i].x <= 25.0f && ballPositions_[i].x >= 20.0f &&
			ballVelocities_[i].x < 0.0f)
		{
			ballVelocities_[i].x *= -1;
		}
	}
}

void Game::generateOutput()
{
	// 1. back buffer�� �ʱ�ȭ
	SDL_SetRenderDrawColor(renderer_, 0, 0, 255, 255);
	SDL_RenderClear(renderer_);

	// 2. ������ �׸���.

	// �� ������ �����Ѵ�.
	SDL_SetRenderDrawColor(renderer_, 210, 210, 210, 255);

	// ���� ��
	SDL_Rect wall = { 0, 0, 1024, thickness };
	SDL_RenderFillRect(renderer_, &wall);

	// �Ʒ��� ��
	wall.y = 768 - thickness;
	SDL_RenderFillRect(renderer_, &wall);

	// ������ ��
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 768;
	SDL_RenderFillRect(renderer_, &wall);

	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);

	for (const auto& position : ballPositions_)
	{
		// ��
		SDL_Rect ball = {
			static_cast<float>(position.x - thickness / 2.0f),
			static_cast<float>(position.y - thickness / 2.0f),
			thickness,
			thickness
		};
		SDL_RenderFillRect(renderer_, &ball);
	}

	// �е�
	SDL_Rect paddle = {
		static_cast<float>(paddlePosition_.x),
		static_cast<float>(paddlePosition_.y - paddleHeight / 2.0f),
		thickness,
		paddleHeight
	};
	SDL_RenderFillRect(renderer_, &paddle);

	// 3. front buffer�� back buffer�� ��ȯ.
	SDL_RenderPresent(renderer_);
}