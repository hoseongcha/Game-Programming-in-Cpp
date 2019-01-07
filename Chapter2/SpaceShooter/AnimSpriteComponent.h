#pragma once

#include "SpriteComponent.h"
#include <vector>

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);

	void update(float deltaTime) override;

	void setAnimTextures(const std::vector<SDL_Texture*>& textures);

	float getAnimFPS() const;
	void setAnimFPS(float fps);

private:
	std::vector<SDL_Texture*> animTextures_;
	float currFrame_;
	float animFPS_;
};