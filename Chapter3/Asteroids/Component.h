#pragma once

#include "SDL/SDL_types.h"

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component() = 0;

	virtual void processInput(const uint8_t* keyState);
	virtual void update(float deltaTime);

	int getUpdateOrder() const;

protected:
	class Actor* getOwner();
	const class Actor* getOwner() const;

private:
	class Actor* owner_;
	int updateOrder_;
};