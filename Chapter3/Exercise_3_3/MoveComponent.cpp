#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
	: Component(owner, updateOrder),
	mass_(1.0f)
{
	totalForce_ = Vector2::Zero;
	velocity_ = Vector2::Zero;
}

void MoveComponent::update(float deltaTime)
{
	Actor* owner = getOwner();

	Vector2 acceleration = Vector2(totalForce_.x / mass_, totalForce_.y / mass_);
	totalForce_ = Vector2::Zero;

	velocity_ += acceleration * deltaTime;

	if (!Math::NearZero(velocity_.LengthSq()))
	{
		Vector2 position = owner->getPosition();
		position += velocity_ * deltaTime;

		if (position.x < 0.0f) { position.x = 1022.0f; }
		else if (position.x > 1024.0f) position.x = 2.0f;

		if (position.y < 0.0f) position.y = 766.0f;
		else if (position.y > 768.0f) position.y = 2.0f;

		owner->setPosition(position);
	}

	if (!Math::NearZero(angularSpeed_))
	{
		float rotation = owner->getRotation();
		rotation += angularSpeed_ * deltaTime;
		owner->setRotation(rotation);
	}
}

void MoveComponent::addForce(const Vector2& force)
{
	totalForce_ += force;
}

float MoveComponent::getMass() const
{
	return mass_;
}

void MoveComponent::setMass(float mass)
{
	mass_ = mass;
}

float MoveComponent::geteAngularSpeed() const
{
	return angularSpeed_;
}
void MoveComponent::setAngularSpeed(float speed)
{
	angularSpeed_ = speed;
}

const Vector2& MoveComponent::getVelocity() const
{
	return velocity_;
}

void MoveComponent::setVelocity(const Vector2 & velocity)
{
	velocity_ = velocity;
}
