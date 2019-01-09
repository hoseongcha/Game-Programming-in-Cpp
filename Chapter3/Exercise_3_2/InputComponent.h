#pragma once

#include "MoveComponent.h"
#include "SDL/SDL_types.h"

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* owner);

	void processInput(const uint8_t* keyState) override;

	float getMaxForwardSpeed() const;
	void setMaxForwardSpeed(float speed);

	float getMaxAngularSpeed() const;
	void setMaxAngularSpeed(float speed);

	int getForwardKey() const;
	void setForwardKey(int key);

	int getBackKey() const;
	void setBackKey(int key);

	int getClockwiseKey() const;
	void setClockwiseKey(int key);

	int getCounterClockwiseKey() const;
	void setCounterClockwiseKey(int key);

private:
	float maxForwardSpeed_;
	float maxAngularSpeed_;

	int forwardKey_;
	int backKey_;
	int clockwiseKey_;
	int counterClockwiseKey_;
};