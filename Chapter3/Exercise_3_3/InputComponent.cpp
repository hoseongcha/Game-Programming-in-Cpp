#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(Actor* owner)
	: MoveComponent(owner),
	forwardKey_(0), backKey_(0),
	clockwiseKey_(0), counterClockwiseKey_(0)
{

}

void InputComponent::processInput(const uint8_t* keyState)
{
	Actor* owner = getOwner();

	float angularSpeed = 0.0f;
	if (keyState[clockwiseKey_])
		angularSpeed += maxAngularSpeed_;
	if (keyState[counterClockwiseKey_])
		angularSpeed -= maxAngularSpeed_;
	setAngularSpeed(angularSpeed);

	float forwardSpeed = 0.0f;
	if (keyState[forwardKey_])
		forwardSpeed += maxForwardSpeed_;
	if (keyState[backKey_])
		forwardSpeed -= maxForwardSpeed_;

	if (Math::NearZero(forwardSpeed))
		setVelocity(Vector2::Zero);
	else if (getVelocity().Length() < maxForwardSpeed_)
		addForce(owner->getForward() * forwardSpeed);
}

float InputComponent::getMaxForwardSpeed() const
{
	return maxForwardSpeed_;
}

void InputComponent::setMaxForwardSpeed(float speed)
{
	maxForwardSpeed_ = speed;
}

float InputComponent::getMaxAngularSpeed() const
{
	return maxAngularSpeed_;
}

void InputComponent::setMaxAngularSpeed(float speed)
{
	maxAngularSpeed_ = speed;
}

int InputComponent::getForwardKey() const
{
	return forwardKey_;
}

void InputComponent::setForwardKey(int key)
{
	forwardKey_ = key;
}

int InputComponent::getBackKey() const
{
	return backKey_;
}

void InputComponent::setBackKey(int key)
{
	backKey_ = key;
}

int InputComponent::getClockwiseKey() const
{
	return clockwiseKey_;
}

void InputComponent::setClockwiseKey(int key)
{
	clockwiseKey_ = key;
}

int InputComponent::getCounterClockwiseKey() const
{
	return counterClockwiseKey_;
}

void InputComponent::setCounterClockwiseKey(int key)
{
	counterClockwiseKey_ = key;
}
