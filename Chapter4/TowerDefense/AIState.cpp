#include "AIState.h"

AIState::AIState(AIComponent* owner)
	: owner_(owner)
{
}

AIComponent* AIState::getOwner()
{
	return owner_;
}
