#pragma once

#include "SpriteComponent.h"

#include <unordered_map>
#include <vector>

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);

	void update(float deltaTime) override;

	void setAnimTextures(const std::vector<SDL_Texture*>& textures);

	float getAnimFPS() const;
	void setAnimFPS(float fps);

#pragma region Exercise2_2
	void setAnimation(const std::string& name, size_t start, size_t end);
	void changeAnimation(const std::string& name, bool isLooping = false);
#pragma endregion

private:
	std::vector<SDL_Texture*> animTextures_;
	float currFrame_;
	float animFPS_;

#pragma region Exercise2_2
	struct AnimInfo
	{
		size_t start;
		size_t end;
	};

	std::unordered_map<std::string, AnimInfo> animations_;
	AnimInfo currAnim_;
	bool isLooping_;
#pragma endregion
};