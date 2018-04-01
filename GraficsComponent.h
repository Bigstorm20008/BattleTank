#pragma once

#include "Grafics2D.h"
#include "SpriteSheet.h"
#include "PlayerTank.h"


class GraficsComponent
{
public:
	GraficsComponent();
	virtual ~GraficsComponent();
	void update(PlayerTank& playerTank, Grafics2D& gfx);
};

