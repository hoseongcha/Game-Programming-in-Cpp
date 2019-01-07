#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder)
	: owner_(owner), updateOrder_(updateOrder)
{
	owner_->addComponent(this);
}

Component::~Component()
{
	owner_->removeComponent(this);
}

void Component::update(float deltaTime)
{
}

int Component::getUpdateOrder() const
{
	return updateOrder_;
}

Actor* Component::getOwner()
{
	return owner_;
}