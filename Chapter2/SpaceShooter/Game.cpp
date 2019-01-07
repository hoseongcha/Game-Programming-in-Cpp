#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"

#include "Ship.h"

#include "SDL/SDL_image.h"

Game::Game()
	: window_(nullptr), renderer_(nullptr),
	isRunning_(true),
	updatingActors_(false)
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

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image : %s", SDL_GetError());
		return false;
	}

	loadData();

	ticksCount_ = SDL_GetTicks();

	return true;
}

void Game::shutdown()
{
	// �ʱ�ȭ �ߴ� �ݴ� ������ �����Ѵ�.
	
	unloadData();
	IMG_Quit();
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

void Game::addActor(Actor* actor)
{
	if (updatingActors_)
		pendingActors_.emplace_back(actor);
	else
		actors_.emplace_back(actor);
}

void Game::removeActor(Actor* actor)
{
	auto iter = std::find(pendingActors_.begin(), pendingActors_.end(), actor);
	if (iter != pendingActors_.end())
	{
		std::iter_swap(iter, pendingActors_.end() - 1);
		pendingActors_.pop_back();
	}
	else
	{
		iter = std::find(actors_.begin(), actors_.end(), actor);
		if (iter != actors_.end())
		{
			std::iter_swap(iter, actors_.end() - 1);
			actors_.pop_back();
		}
	}
}

void Game::addSprite(SpriteComponent* sprite)
{
	int drawOrder = sprite->getDrawOrder();
	auto iter = sprites_.begin();

	while (iter != sprites_.end())
	{
		if (drawOrder < (*iter)->getDrawOrder())
			break;

		++iter;
	}

	sprites_.insert(iter, sprite);
}

void Game::removeSprite(SpriteComponent* sprite)
{
	auto iter = std::find(sprites_.begin(), sprites_.end(), sprite);
	if (iter != sprites_.end()) sprites_.erase(iter);
}

SDL_Texture* Game::loadTexture(const std::string& filename)
{
	SDL_Texture* texture = nullptr;

	auto iter = textures_.find(filename);
	if (iter != textures_.end())
		texture = iter->second;
	else
	{
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface)
		{
			SDL_Log("Failed to load texture file %s", filename.c_str());
			return nullptr;
		}

		texture = SDL_CreateTextureFromSurface(renderer_, surface);
		SDL_FreeSurface(surface);

		if (!texture)
		{
			SDL_Log("Failed to convert surface to texture for %s", filename.c_str());
			return false;
		}

		textures_.emplace(filename.c_str(), texture);
	}

	return texture;
}

void Game::loadData()
{
	ship_ = new Ship(this);
	ship_->setPosition(Vector2(100.0f, 384.0f));
	ship_->setScale(1.5f);

	Actor* bgActor = new Actor(this);
	bgActor->setPosition(Vector2(512.0f, 384.0f));

	BGSpriteComponent* bg = new BGSpriteComponent(bgActor);
	bg->setScreenSize(Vector2(1024.0f, 768.0f));
	std::vector<SDL_Texture*> bgTextures = {
		loadTexture("Assets/Farback01.png"),
		loadTexture("Assets/Farback02.png")
	};
	bg->setBGTextures(bgTextures);
	bg->setScrollSpeed(-100.0f);
	
	bg = new BGSpriteComponent(bgActor, 50);
	bg->setScreenSize(Vector2(1024.0f, 768.0f));
	bgTextures = {
		loadTexture("Assets/Stars.png"),
		loadTexture("assets/Stars.png")
	};
	bg->setBGTextures(bgTextures);
	bg->setScrollSpeed(-200.0f);
}

void Game::unloadData()
{
	// Actor�� �Ҹ��ڿ��� �ڵ����� ���� ��Ͽ��� �ڽ��� �����.
	while (!actors_.empty())
		delete actors_.back();

	for (auto element : textures_)
		SDL_DestroyTexture(element.second);
	textures_.clear();
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

	ship_->processKeyboard(state);
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

	// ���͸� ������Ʈ�Ѵ�.
	updatingActors_ = true;
	for (auto actor : actors_)
		actor->update(deltaTime);
	updatingActors_ = false;

	// ���͸� ������Ʈ �ϸ鼭 ���� ���ο� ���͸�
	// ���� ��Ͽ� �߰��Ѵ�.
	for (auto actor : pendingActors_)
		actors_.emplace_back(actor);
	pendingActors_.clear();

	// �����߿� ������ �� �� ���͸� ������.
	std::vector<Actor*> deadActors;
	for (auto actor : actors_)
	{
		if (actor->getState() == Actor::State::Dead)
			deadActors.emplace_back(actor);
	}

	// ������ �� �� ���͵��� ��Ͽ��� �����.
	for (auto actor : deadActors)
		delete actor;
}

void Game::generateOutput()
{
	// 1. back buffer�� �ʱ�ȭ
	SDL_SetRenderDrawColor(renderer_, 0, 0, 255, 255);
	SDL_RenderClear(renderer_);

	// 2. ������ �׸���.

	
	// 3. front buffer�� back buffer�� ��ȯ.
	SDL_RenderPresent(renderer_);
}
