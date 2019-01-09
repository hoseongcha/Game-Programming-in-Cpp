#pragma once

#define SDL_MAIN_HANDLED
#include "SDL/SDL.h"

#include <unordered_map>
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

	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);

	SDL_Texture* loadTexture(const std::string& filename);

	// Chapter3 코드
	void addAsteroid(class Asteroid* asteroid);
	void removeAsteroid(class Asteroid* asteroid);

	std::vector<class Asteroid*>& getAsteroids();

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

	std::unordered_map<std::string, SDL_Texture*> textures_;

	std::vector<class Actor*> actors_;
	std::vector<class Actor*> pendingActors_;

	std::vector<class SpriteComponent*> sprites_;

	// Chapter3 코드
	std::vector<class Asteroid*> asteroids_;
	class Ship* ship_;

	bool isRunning_;
	bool updatingActors_;
};