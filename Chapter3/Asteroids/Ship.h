#pragma once

#include "Actor.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);

	void updateActor(float deltaTime) override;
	void actorInput(const uint8_t* keyState) override;

private:
	float laserCooldown_;
};