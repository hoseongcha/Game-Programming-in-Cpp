#pragma once

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void update(float deltaTime);

	int getUpdateOrder() const;

protected:
	class Actor* getOwner();

private:
	class Actor* owner_;
	int updateOrder_;
};