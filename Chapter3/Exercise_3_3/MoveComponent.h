#pragma once

#include "Component.h"
#include "Math.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void update(float deltaTime) override;

	void addForce(const Vector2& force);
	
	float getMass() const;
	void setMass(float mass);

	float geteAngularSpeed() const;
	void setAngularSpeed(float speed);

	const Vector2& getVelocity() const;
	void setVelocity(const Vector2& velocity);

private:
	Vector2 totalForce_;
	float mass_;
	Vector2 velocity_;
	float angularSpeed_;
};