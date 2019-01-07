#include "Ship.h"
#include "Game.h"

#include "AnimSpriteComponent.h"

Ship::Ship(Game* game)
	: Actor(game),
	rightSpeed_(0.0f), downSpeed_(0.0f)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->loadTexture("Assets/Ship01.png"),
		game->loadTexture("Assets/Ship02.png"),
		game->loadTexture("Assets/Ship03.png"),
		game->loadTexture("Assets/Ship04.png")
	};
	asc->setAnimTextures(anims);
}

void Ship::processKeyboard(const uint8_t* state)
{
	rightSpeed_ = 0.0f;
	downSpeed_ = 0.0f;

	// 오른쪽/왼쪽
	if (state[SDL_SCANCODE_D])
		rightSpeed_ += 250.0f;
	if (state[SDL_SCANCODE_A])
		rightSpeed_ -= 250.0f;

	// 위/아래
	if (state[SDL_SCANCODE_S])
		downSpeed_ += 300.0f;
	if (state[SDL_SCANCODE_W])
		downSpeed_ -= 300.0f;
}

void Ship::updateActor(float deltaTime)
{
	Actor::updateActor(deltaTime);

	Vector2 position = getPosition();
	position.x += rightSpeed_ * deltaTime;
	position.y += downSpeed_ * deltaTime;

	if (position.x < 25.0f)
		position.x = 25.0f;
	else if (position.x > 500.0f)
		position.x = 500.0f;

	if (position.y < 25.0f)
		position.y = 25.0f;
	else if (position.y > 743.0f)
		position.y = 743.0f;

	setPosition(position);
}