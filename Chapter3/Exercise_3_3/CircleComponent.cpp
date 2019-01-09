#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner)
	: Component(owner)
{

}

void CircleComponent::setRadius(float radius)
{
	radius_ = radius;
}

float CircleComponent::getRadius() const
{
	return radius_;
}

const Vector2& CircleComponent::getCenter() const
{
	return getOwner()->getPosition();
}

bool Intersect(const CircleComponent& lhs, const CircleComponent& rhs)
{
	Vector2 diff = lhs.getCenter() - rhs.getCenter();
	float distSq = diff.LengthSq();

	float radiiSq = lhs.getRadius() + rhs.getRadius();
	radiiSq *= radiiSq;

	return distSq <= radiiSq;
}
