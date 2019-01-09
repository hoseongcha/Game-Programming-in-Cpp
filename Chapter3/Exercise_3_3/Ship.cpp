#include "Ship.h"
#include "Game.h"

#include "SpriteComponent.h"
#include "InputComponent.h"

Ship::Ship(Game* game)
	: Actor(game)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->setTexture(game->loadTexture("../Assets/Ship.png"));

	InputComponent* mc = new InputComponent(this);
	mc->setForwardKey(SDL_SCANCODE_W);
	mc->setBackKey(SDL_SCANCODE_S);
	mc->setClockwiseKey(SDL_SCANCODE_A);
	mc->setCounterClockwiseKey(SDL_SCANCODE_D);
	mc->setMaxForwardSpeed(300.0f);
	mc->setMass(2.5f);
	mc->setMaxAngularSpeed(Math::TwoPi);
}