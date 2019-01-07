#pragma once

#include "Component.h"

#include "SDL/SDL.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void draw(SDL_Renderer* renderer);

	virtual void setTexture(SDL_Texture* texture);

	int getDrawOrder() const;
	int getTextureWidth() const;
	int getTextureHeight() const;

private:
	SDL_Texture* texture_;
	int drawOrder_;
	int textureWidth_;
	int textureHeight_;
};