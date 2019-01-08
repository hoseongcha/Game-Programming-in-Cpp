#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	: Component(owner),
	drawOrder_(drawOrder)
{
	owner->getGame()->addSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	getOwner()->getGame()->removeSprite(this);
}

void SpriteComponent::draw(SDL_Renderer* renderer)
{
	if (!texture_)
		return;

	Actor* owner = getOwner();

	SDL_Rect r;
	r.w = static_cast<int>(textureWidth_ * owner->getScale());
	r.h = static_cast<int>(textureHeight_ * owner->getScale());
	r.x = static_cast<int>(owner->getPosition().x - r.w / 2);
	r.y = static_cast<int>(owner->getPosition().y - r.h / 2);

	SDL_RenderCopyEx(renderer,
		texture_,
		nullptr,
		&r,
		-Math::ToDegrees(owner->getRotation()),
		nullptr,
		SDL_FLIP_NONE);
}

void SpriteComponent::setTexture(SDL_Texture* texture)
{
	texture_ = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth_, &textureHeight_);
}

int SpriteComponent::getDrawOrder() const
{
	return drawOrder_;
}

int SpriteComponent::getTextureWidth() const
{
	return textureWidth_;
}

int SpriteComponent::getTextureHeight() const
{
	return textureHeight_;
}

SDL_Texture * SpriteComponent::getTexture()
{
	return texture_;
}
