#pragma once

#include "Math.h"

#include <vector>

class Actor
{
public:
	enum class State
	{
		Active,
		Paused,
		Dead,
	};

	Actor(class Game* game);
	virtual ~Actor();

	void processInput(const uint8_t* keyState);
	void update(float deltaTime);
	
	State getState() const;
	void setState(State state);

	const Vector2& getPosition() const;
	void setPosition(const Vector2& position);

	float getRotation() const;
	void setRotation(float rotation);

	float getScale() const;
	void setScale(float scale);

	Vector2 getForward() const;

	class Game* getGame();

	void addComponent(class Component* component);
	void removeComponent(class Component* component);

protected:
	virtual void actorInput(const uint8_t* keyState);
	virtual void updateActor(float deltaTime);

private:
	void updateComponents(float deltaTime);

private:
	State state_;

	Vector2 position_;
	float rotation_;
	float scale_;

	std::vector<class Component*> components_;
	class Game* game_;
};