#include "Asteroid.h"
#include "Game.h"
#include "Random.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game* game)
	: Actor(game)
{
	Vector2 randPosition = Random::GetVector(Vector2::Zero,
		Vector2(1024.0f, 768.0f));
	setPosition(randPosition);
	setRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	SpriteComponent* sc = new SpriteComponent(this);
	sc->setTexture(game->loadTexture("../Assets/Asteroid.png"));

	move_ = new MoveComponent(this);
	move_->setMass(2.5f);
	move_->addForce(getForward() * 15000.0f);

	circle_ = new CircleComponent(this);
	circle_->setRadius(40.0f);

	game->addAsteroid(this);
}

Asteroid::~Asteroid()
{
	getGame()->removeAsteroid(this);
}

CircleComponent* Asteroid::getCircle()
{
	return circle_;
}
