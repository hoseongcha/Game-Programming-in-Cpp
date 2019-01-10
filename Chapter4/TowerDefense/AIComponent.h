#pragma once

#include "Component.h"

#include <string>
#include <unordered_map>\

class AIComponent : public Component
{
public:
	AIComponent(class Actor* owner);

	void update(float deltaTime) override;

	void registerState(class AIState* state);
	void changeState(const std::string& name);

private:
	std::unordered_map<std::string, class AIState*> stateMap_;
	class AIState* currentState_;
};