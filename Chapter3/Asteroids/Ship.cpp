#include "Ship.h"
#include "Game.h"

#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Laser.h"

Ship::Ship(Game* game)
	: Actor(game),
	laserCooldown_(0.5f)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->setTexture(game->loadTexture("../Assets/Ship.png"));

	InputComponent* ic = new InputComponent(this);
	ic->setForwardKey(SDL_SCANCODE_W);
	ic->setBackKey(SDL_SCANCODE_S);
	ic->setClockwiseKey(SDL_SCANCODE_A);
	ic->setCounterClockwiseKey(SDL_SCANCODE_D);
	ic->setMaxForwardSpeed(300.0f);
	ic->setMaxAngularSpeed(Math::TwoPi);
}

void Ship::updateActor(float deltaTime)
{
	laserCooldown_ -= deltaTime;
}

void Ship::actorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && laserCooldown_ <= 0.0f)
	{
		Laser* laser = new Laser(getGame());
		laser->setPosition(getPosition());
		laser->setRotation(getRotation());

		laserCooldown_ = 0.5f;
	}
}