#include "AnimSpriteComponent.h"
#include "Actor.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder),
	currFrame_(0.0f),
	animFPS_(24.0f)
{

}

void AnimSpriteComponent::update(float deltaTime)
{
	SpriteComponent::update(deltaTime);

	if (animTextures_.size() == 0)
		return;

	currFrame_ += animFPS_ * deltaTime;

	while (currFrame_ >= animTextures_.size())
		currFrame_ -= animTextures_.size();

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