#include "exercise1_1.h"

const int thickness = 15;
const float paddleHeight = 100;

Game::Game()
	: window_(nullptr), renderer_(nullptr),
	ticksCount_(0),
	leftPaddleDirection_(0), rightPaddleDirection_(0),
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

	leftPaddlePosition_.x = 10;
	leftPaddlePosition_.y = 768 / 2.0f;

	rightPaddlePosition_.x = 1024 - thickness - 10;
	rightPaddlePosition_.y = 768 / 2.0f;

	ballPosition_.x = 1024 / 2.0f;
	ballPosition_.y = 768 / 2.0f;

	ballVelocity_.x = -200.0f;
	ballVelocity_.y = 235.0f;

	return true;
}

void Game::shutdown()
{
	// 초기화 했던 반대 순서로 종료한다.

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

	leftPaddleDirection_ = 0;
	if (state[SDL_SCANCODE_W])
		leftPaddleDirection_ -= 1;
	if (state[SDL_SCANCODE_S])
		leftPaddleDirection_ += 1;

	rightPaddleDirection_ = 0;
	if (state[SDL_SCANCODE_U])
		rightPaddleDirection_ -= 1;
	if (state[SDL_SCANCODE_J])
		rightPaddleDirection_ += 1;
}

void Game::updateGame()
{
	// 경과 시간이 목표한 프레임 시간보다 더 빠를때, (여기서는 목표 프레임 시간은 60FPS)
	// 60FPS가 될때까지 기다린다.
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount_ + 16))
		;

	float deltaTime = (SDL_GetTicks() - ticksCount_) / 1000.0f;

	// 경과 시간이 목표한 프레임 시간보다 더 느리면,
	// 경과 시간을 0.05f로 제한한다.
	if (deltaTime > 0.05f)
		deltaTime = 0.05f;

	ticksCount_ = SDL_GetTicks();

	if (leftPaddleDirection_ != 0)
	{
		leftPaddlePosition_.y += leftPaddleDirection_ * 300.0f * deltaTime;

		if (leftPaddlePosition_.y < (paddleHeight / 2.0f + thickness))
			leftPaddlePosition_.y = paddleHeight / 2.0f + thickness;
		else if (leftPaddlePosition_.y > (768.0f - paddleHeight / 2.0f - thickness))
			leftPaddlePosition_.y = 768.0f - paddleHeight / 2.0f - thickness;
	}

	if (rightPaddleDirection_ != 0)
	{
		rightPaddlePosition_.y += rightPaddleDirection_ * 300.0f * deltaTime;

		if (rightPaddlePosition_.y < (paddleHeight / 2.0f + thickness))
			rightPaddlePosition_.y = paddleHeight / 2.0f + thickness;
		else if (rightPaddlePosition_.y > (768.0f - paddleHeight / 2.0f - thickness))
			rightPaddlePosition_.y = 768.0f - paddleHeight / 2.0f - thickness;
	}

	ballPosition_.x += ballVelocity_.x * deltaTime;
	ballPosition_.y += ballVelocity_.y * deltaTime;

	if (ballPosition_.y < thickness && ballVelocity_.y < 0.0f)
		ballVelocity_.y *= -1;
	else if (ballPosition_.y > 768.0f - thickness && ballVelocity_.y > 0.0f)
		ballVelocity_.y *= -1;

	float diff = fabs(leftPaddlePosition_.y - ballPosition_.y);
	if (diff <= paddleHeight / 2.0f &&
		ballPosition_.x <= 25.0f && ballPosition_.x >= 20.0f &&
		ballVelocity_.x < 0.0f)
	{
		ballVelocity_.x *= -1;
	}

	diff = fabs(rightPaddlePosition_.y - ballPosition_.y);
	if (diff <= paddleHeight / 2.0f &&
		ballPosition_.x <= 1004.0f && ballPosition_.x >= 999.0f &&
		ballVelocity_.x > 0.0f)
	{
		ballVelocity_.x *= -1;
	}
}

void Game::generateOutput()
{
	// 1. back buffer를 초기화
	SDL_SetRenderDrawColor(renderer_, 0, 0, 255, 255);
	SDL_RenderClear(renderer_);

	// 2. 게임을 그린다.

	// 벽 색깔을 설정한다.
	SDL_SetRenderDrawColor(renderer_, 210, 210, 210, 255);

	// 위쪽 벽
	SDL_Rect wall = { 0, 0, 1024, thickness };
	SDL_RenderFillRect(renderer_, &wall);

	// 아래쪽 벽
	wall.y = 768 - thickness;
	SDL_RenderFillRect(renderer_, &wall);

	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
	// 공
	SDL_Rect ball = {
		static_cast<float>(ballPosition_.x - thickness / 2.0f),
		static_cast<float>(ballPosition_.y - thickness / 2.0f),
		thickness,
		thickness
	};
	SDL_RenderFillRect(renderer_, &ball);

	// 왼쪽 패들
	SDL_Rect paddle = {
		static_cast<float>(leftPaddlePosition_.x),
		static_cast<float>(leftPaddlePosition_.y - paddleHeight / 2.0f),
		thickness,
		paddleHeight
	};
	SDL_RenderFillRect(renderer_, &paddle);

	// 오른쪽 패들
	paddle.x = static_cast<float>(rightPaddlePosition_.x);
	paddle.y = static_cast<float>(rightPaddlePosition_.y - paddleHeight / 2.0f);
	paddle.w = thickness;
	paddle.h = paddleHeight;
	SDL_RenderFillRect(renderer_, &paddle);

	// 3. front buffer와 back buffer를 교환.
	SDL_RenderPresent(renderer_);
}