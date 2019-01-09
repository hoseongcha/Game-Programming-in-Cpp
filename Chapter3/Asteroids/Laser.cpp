#include "Laser.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Asteroid.h"

Laser::Laser(Game* game)
	: Actor(game),
	deathTimer_(1.0f)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->setTexture(game->loadTexture("../Assets/Laser.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->setForwardSpeed(800.0f);

	circle_ = new CircleComponent(this);
	circle_->setRadius(11.0f);
}

void Laser::updateActor(float deltaTime)
{
	deathTimer_ -= deltaTime;

	if (deathTimer_ <= 0.0f)
	{
		setState(State::Dead);
	}
	else
	{
		for (auto asteroid : getGame()->getAsteroids())
		{
			if (Intersect(*circle_, *(asteroid->getCircle())))
			{
				setState(State::Dead);
				asteroid->setState(State::Dead);
				break;
			}
		}
	}
}
