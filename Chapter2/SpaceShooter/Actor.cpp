#include "Actor.h"
#include "Game.h"
#include "Component.h"

Actor::Actor(Game* game)
	: state_(State::Active),
	position_(Vector2::Zero), rotation_(0.0f), scale_(1.0f),
	game_(game)
{
	game_->addActor(this);
}

Actor::~Actor()
{
	game_->removeActor(this);

	// Component 클래스의 소멸자에서 Actor::removeComponent 함수를 호출해서
	// 자동으로 Actor::components_에서 제거된다 
	while (!components_.empty())
		delete components_.back();
}

void Actor::update(float deltaTime)
{
	if (state_ == State::Active)
	{
		updateComponents(deltaTime);
		updateActor(deltaTime);
	}
}

Actor::State Actor::getState() const
{
	return state_;
}

void Actor::setState(Actor::State state)
{
	state_ = state;
}

const Vector2& Actor::getPosition() const
{
	return position_;
}

void Actor::setPosition(const Vector2& position)
{
	position_ = position;
}

float Actor::getRotation() const
{
	return rotation_;
}

void Actor::setRotation(float rotation)
{
	rotation_ = rotation;
}

float Actor::getScale() const
{
	return scale_;
}

void Actor::setScale(float scale)
{
	scale_ = scale;
}

Game* Actor::getGame()
{
	return game_;
}

void Actor::addComponent(Component* component)
{
	// updateOrder가 낮은 순으로 compoent를 저장한다.
	// updateOrder의 우선순위는 값이 클수록 낮다.

	int order = component->getUpdateOrder();
	auto iter = components_.begin();

	while (iter != components_.end())
	{
		if (order < (*iter)->getUpdateOrder())
			break;

		++iter;
	}

	components_.insert(iter, component);
}

void Actor::removeComponent(Component* component)
{
	auto iter = std::find(components_.begin(), components_.end(), component);
	if (iter != components_.end()) components_.erase(iter);
}

void Actor::updateComponents(float deltaTime)
{
	for (auto component : components_)
		component->update(deltaTime);
}

void Actor::updateActor(float deltaTime)
{

}