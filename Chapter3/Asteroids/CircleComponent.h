#pragma once

#include "Component.h"
#include "Math.h"

class CircleComponent : public Component
{
public:
	CircleComponent(class Actor* owner);

	void setRadius(float radius);
	float getRadius() const;

	const Vector2& getCenter() const;

private:
	float radius_;
};

bool Intersect(const CircleComponent& lhs, const CircleComponent& rhs);