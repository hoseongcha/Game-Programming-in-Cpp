#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"

#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "TileMapComponent.h"

#include "SDL/SDL_image.h"

#include <sstream>

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
	// 초기화 했던 반대 순서로 종료한다.
	
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
	/*ship_ = new Ship(this);
	ship_->setPosition(Vector2(100.0f, 384.0f));
	ship_->setScale(1.5f);*/

#pragma region Exercise2_2
	/*Actor* skeleton = new Actor(this);
	skeleton->setPosition(Vector2(100.0f, 700.0f));
	asc_ = new AnimSpriteComponent(skeleton);
	
	std::vector<SDL_Texture*> animTextures(18);
	for (int i = 0; i < 18; ++i)
	{
		std::ostringstream oss;
		oss << "Assets/Character" << (i < 9 ? "0" : "") << i + 1 << ".png";
		animTextures[i] = loadTexture(oss.str());
	}

	asc_->setAnimTextures(animTextures);
	asc_->setAnimation("Walking", 0, 5);
	asc_->setAnimation("Jumping", 6, 14);
	asc_->setAnimation("Punch", 15, 17);*/
#pragma endregion

	Actor* tileMapActor = new Actor(this);
	tileMapActor->setPosition(Vector2(512.0f, 384.0f));

	TileMapComponent* tileMap = new TileMapComponent(tileMapActor, 100);
	tileMap->readMapData("Assets/MapLayer1.csv");
	tileMap->setUnit(32);
	tileMap->setTexture(loadTexture("Assets/Tiles.png"));

	tileMap = new TileMapComponent(tileMapActor, 50);
	tileMap->readMapData("Assets/MapLayer2.csv");
	tileMap->setUnit(32);
	tileMap->setTexture(loadTexture("Assets/Tiles.png"));

	tileMap = new TileMapComponent(tileMapActor);
	tileMap->readMapData("Assets/MapLayer3.csv");
	tileMap->setUnit(32);
	tileMap->setTexture(loadTexture("Assets/Tiles.png"));
	
	/*Actor* bgActor = new Actor(this);
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
	bg->setScrollSpeed(-200.0f);*/
}

void Game::unloadData()
{
	/*delete ship_;*/

	// Actor의 소멸자에서 자동으로 액터 목록에서 자신을 지운다.
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

	/*ship_->processKeyboard(state);*/
#pragma region Exercise2_2
	/*if (state[SDL_SCANCODE_W])
	{
		asc_->changeAnimation("Walking", false);
		asc_->setAnimFPS(8);
	}
	if (state[SDL_SCANCODE_SPACE])
	{
		asc_->changeAnimation("Jumping", false);
		asc_->setAnimFPS(8);
	}
	if (state[SDL_SCANCODE_P])
	{
		asc_->changeAnimation("Punch", false);
		asc_->setAnimFPS(8);
	}*/
#pragma endregion
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

	// 액터를 업데이트한다.
	updatingActors_ = true;
	for (auto actor : actors_)
		actor->update(deltaTime);
	updatingActors_ = false;

	// 액터를 업데이트 하면서 생긴 새로운 액터를
	// 액터 목록에 추가한다.
	for (auto actor : pendingActors_)
		actors_.emplace_back(actor);
	pendingActors_.clear();

	// 액터중에 수명이 다 한 액터를 모은다.
	std::vector<Actor*> deadActors;
	for (auto actor : actors_)
	{
		if (actor->getState() == Actor::State::Dead)
			deadActors.emplace_back(actor);
	}

	// 수명이 다 한 액터들은 목록에서 지운다.
	for (auto actor : deadActors)
		delete actor;
}

void Game::generateOutput()
{
	// 1. back buffer를 초기화
	SDL_SetRenderDrawColor(renderer_, 0, 0, 255, 255);
	SDL_RenderClear(renderer_);

	// 2. 게임을 그린다.
	for (auto sprite : sprites_)
		sprite->draw(renderer_);
	
	// 3. front buffer와 back buffer를 교환.
	SDL_RenderPresent(renderer_);
}
