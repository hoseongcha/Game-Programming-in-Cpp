#pragma once

#include "SpriteComponent.h"
#include "Math.h"

#include <vector>

class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(class Actor* owner, int drawOrder = 10);
	
	void draw(SDL_Renderer* renderer) override;

	void readMapData(const std::string& filename);
	
	void setUnit(int unit);
	int getUnit() const;

private:
	std::vector<std::vector<int>> mapData_;
	int unit_;
};