#pragma once

#include "Component.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void update(float deltaTime) override;

	float getAngularSpeed() const;
	void setAngularSpeed(float speed);

	float getForwardSpeed() const;
	void setForwardSpeed(float speed);

private:
	float angularSpeed_;
	float forwardSpeed_;
};