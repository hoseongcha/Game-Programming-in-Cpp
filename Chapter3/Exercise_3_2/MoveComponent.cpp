#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
	: Component(owner, updateOrder),
	angularSpeed_(0.0f),
	forwardSpeed_(0.0f)
{

}

void MoveComponent::update(float deltaTime)
{
	Actor* owner = getOwner();

	if (!Math::NearZero(angularSpeed_))
	{
		float rotation = owner->getRotation();
		rotation += angularSpeed_ * deltaTime;
		owner->setRotation(rotation);
	}

	if (!Math::NearZero(forwardSpeed_))
	{
		Vector2 position = owner->getPosition();
		position += owner->getForward() * forwardSpeed_ * deltaTime;
		
		// Chapter3에서만 사용하는 코드
		// screen wrapping
		if (position.x < 0.0f) { position.x = 1022.0f; }
		else if (position.x > 1024.0f) position.x = 2.0f;

		if (position.y < 0.0f) position.y = 766.0f;
		else if (position.y > 768.0f) position.y = 2.0f;

		owner->setPosition(position);
	}
}

float MoveComponent::getAngularSpeed() const
{
	return angularSpeed_;
}

void MoveComponent::setAngularSpeed(float speed)
{
	angularSpeed_ = speed;
}

float MoveComponent::getForwardSpeed() const
{
	return forwardSpeed_;
}

void MoveComponent::setForwardSpeed(float speed)
{
	forwardSpeed_ = speed;
}
