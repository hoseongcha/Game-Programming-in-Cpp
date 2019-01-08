#include "AnimSpriteComponent.h"
#include "Actor.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder),
	currFrame_(0.0f),
	animFPS_(24.0f)
{
#pragma region Exercise2_2
	currAnim_.start = 0;
	currAnim_.end = 0;
	isLooping_ = false;
#pragma endregion
}

void AnimSpriteComponent::update(float deltaTime)
{
	SpriteComponent::update(deltaTime);

	/*if (animTextures_.size() == 0)
		return;

	currFrame_ += animFPS_ * deltaTime;

	while (currFrame_ >= animTextures_.size())
		currFrame_ -= animTextures_.size();*/

#pragma region Exercise2_2
	size_t size = currAnim_.end - currAnim_.start;

	if (animTextures_.size() == 0 || size == 0)
		return;

	currFrame_ += animFPS_ * deltaTime;

	if (isLooping_)
	{
		while (currFrame_ > currAnim_.end)
			currFrame_ -= size;
	}
	else
	{
		if (currFrame_ > currAnim_.end)
			currFrame_ = currAnim_.end;
	}
#pragma endregion

	setTexture(animTextures_[static_cast<int>(currFrame_)]);
}

void AnimSpriteComponent::setAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	animTextures_ = textures;
	if (animTextures_.size() > 0)
	{
		currFrame_ = 0.0f;
		setTexture(animTextures_[0]);
	}
}

float AnimSpriteComponent::getAnimFPS() const
{
	return animFPS_;
}

void AnimSpriteComponent::setAnimFPS(float fps)
{
	animFPS_ = fps;
}

#pragma region Exercise2_2
void AnimSpriteComponent::setAnimation(const std::string& name, size_t start, size_t end)
{
	AnimInfo animInfo = { start, end };
	animations_[name] = std::move(animInfo);
}

void AnimSpriteComponent::changeAnimation(const std::string& name, bool isLooping)
{
	auto iter = animations_.find(name);
	if (iter != animations_.end())
	{
		currAnim_ = iter->second;
		currFrame_ = currAnim_.start;
		isLooping_ = isLooping;

		setTexture(animTextures_[currAnim_.start]);
	}
	else
	{
		currAnim_.start = 0;
		currAnim_.end = 0;
		currFrame_ = 0.0f;
		isLooping_ = isLooping;

	}
}
#pragma endregion