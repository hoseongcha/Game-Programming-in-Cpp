#pragma once

#include "Actor.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);

	void processKeyboard(const uint8_t* state);
	void updateActor(float deltaTime) override;

	float getRightSpeed() const;
	float getDownSpeed() const;

private:
	float rightSpeed_;
	float downSpeed_;
};