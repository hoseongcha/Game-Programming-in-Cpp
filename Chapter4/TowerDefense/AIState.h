#pragma once

class AIState
{
public:
	AIState(class AIComponent* owner);

	virtual void update(float deltaTime) = 0;
	
	virtual void onEnter() = 0;
	virtual void onExit() = 0;

	virtual const char* getName() const = 0;

protected:
	class AIComponent* getOwner();

private:
	class AIComponent* owner_;
};