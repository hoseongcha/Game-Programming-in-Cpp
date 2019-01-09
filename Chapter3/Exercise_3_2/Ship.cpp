#include "Ship.h"
#include "Game.h"

#include "SpriteComponent.h"
#include "InputComponent.h"
#include "CircleComponent.h"

#include "Asteroid.h"
#include "Laser.h"

Ship::Ship(Game* game)
	: Actor(game),
	laserCooldown_(0.5f),
	respawnTimer_(2.0f),
	isCollide_(false)
{
	sprite_ = new SpriteComponent(this);
	sprite_->setTexture(game->loadTexture("../Assets/Ship.png"));

	InputComponent* ic = new InputComponent(this);
	ic->setForwardKey(SDL_SCANCODE_W);
	ic->setBackKey(SDL_SCANCODE_S);
	ic->setClockwiseKey(SDL_SCANCODE_A);
	ic->setCounterClockwiseKey(SDL_SCANCODE_D);
	ic->setMaxForwardSpeed(300.0f);
	ic->setMaxAngularSpeed(Math::TwoPi);

	circle_ = new CircleComponent(this);
	circle_->setRadius(35.0f);
}

void Ship::updateActor(float deltaTime)
{
	laserCooldown_ -= deltaTime;
	
	if (isCollide_)
	{
		respawnTimer_ -= deltaTime;

		if (respawnTimer_ <= 0.0f)
		{
			respawnTimer_ = 2.0f;
			isCollide_ = false;
			getGame()->addSprite(sprite_);
		}
	}
	else
	{
		for (auto asteroid : getGame()->getAsteroids())
		{
			if (Intersect(*circle_, *(asteroid->getCircle())))
			{
				setPosition(Vector2(1024.0f / 2.0f, 768.0f / 2.0f));
				setRotation(0.0f);

				isCollide_ = true;
				getGame()->removeSprite(sprite_);
			}
		}
	}
}

void Ship::actorInput(const uint8_t* keyState)
{
	if (isCollide_)
		return;

	if (keyState[SDL_SCANCODE_SPACE] && laserCooldown_ <= 0.0f)
	{
		Laser* laser = new Laser(getGame());
		laser->setPosition(getPosition());
		laser->setRotation(getRotation());

		laserCooldown_ = 0.5f;
	}
}