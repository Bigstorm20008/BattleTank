#pragma once

#include "GraficsComponent.h"
#include "SpriteSheet.h"

class WallBlockGraficsComponent
	: public GraficsComponent
{
public:
	WallBlockGraficsComponent(Grafics2D& gfx);
	~WallBlockGraficsComponent();
	void update(GameObject* gameobject) override;
private:
	SpriteSheet* m_WallBlockGrafics;
};

