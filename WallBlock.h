#pragma once


#include "GameObject.h"
#include "WallBlockGraficsComponent.h"


class WallBlock :
	public GameObject
{
public:
	WallBlock(WallBlockGraficsComponent* wallBlockGrafcs);
	~WallBlock();

	void update() override;
	void render() override;
};

