#include "AIComponent.h"
#include "AIState.h"

#include "SDL/SDL_log.h"

AIComponent::AIComponent(Actor* owner)
	: Component(owner),
	currentState_(nullptr)
{
}

void AIComponent::update(float deltaTime)
{
	if (currentState_)
		currentState_->update(deltaTime);
}

void AIComponent::registerState(AIState* state)
{
	stateMap_.emplace(state->getName(), state);
}

void AIComponent::changeState(const std::string& name)
{
	if (currentState_)
		currentState_->onExit();

	auto iter = stateMap_.find(name);
	if (iter != stateMap_.end())
	{
		currentState_ = iter->second;
		currentState_->onEnter();
	}
	else
	{
		SDL_Log("Could not find AIState %s in state map", name.c_str());
		currentState_ = nullptr;
	}
}
