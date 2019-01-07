#pragma once

#include "SpriteComponent.h"
#include "Math.h"

#include <vector>

class BGSpriteComponent : public SpriteComponent
{
public:
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);

	void update(float deltaTime) override;
	void draw(SDL_Renderer* renderer) override;

	void setBGTextures(const std::vector<SDL_Texture*>& textures);
	void setScreenSize(const Vector2& size);

	float getScrollSpeed() const;
	void setScrollSpeed(float speed);

private:
	struct BGTexture
	{
		SDL_Texture* texture;
		Vector2 offset;
	};

	std::vector<BGTexture> BGTextures_;
	Vector2 screenSize_;
	float scrollSpeed_;
};