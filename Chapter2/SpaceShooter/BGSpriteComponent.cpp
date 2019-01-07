#include "BGSpriteComponent.h"
#include "Actor.h"

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder),
	scrollSpeed_(0.0f)
{

}

void BGSpriteComponent::update(float deltaTime)
{
	SpriteComponent::update(deltaTime);

	for (auto& bg : BGTextures_)
	{
		bg.offset.x += scrollSpeed_ * deltaTime;
		if (bg.offset.x < -screenSize_.x)
			bg.offset.x = (BGTextures_.size() - 1) * screenSize_.x - 1;
	}
}

void BGSpriteComponent::draw(SDL_Renderer* renderer)
{
	Actor* owner = getOwner();

	for (auto& bg : BGTextures_)
	{
		SDL_Rect r;
		r.w = static_cast<int>(screenSize_.x);
		r.h = static_cast<int>(screenSize_.y);
		r.x = static_cast<int>(owner->getPosition().x - r.w / 2 + bg.offset.x);
		r.y = static_cast<int>(owner->getPosition().y - r.h / 2 + bg.offset.y);

		SDL_RenderCopy(renderer, bg.texture, nullptr, &r);
	}
}

void BGSpriteComponent::setBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;

	for (auto texture : textures)
	{
		BGTexture temp;
		temp.texture = texture;
		temp.offset.x = count * screenSize_.x;
		temp.offset.y = 0;
		BGTextures_.emplace_back(temp);
		++count;
	}
}

void BGSpriteComponent::setScreenSize(const Vector2& size)
{
	screenSize_ = size;
}

float BGSpriteComponent::getScrollSpeed() const
{
	return scrollSpeed_;
}

void BGSpriteComponent::setScrollSpeed(float speed)
{
	scrollSpeed_ = speed;
}