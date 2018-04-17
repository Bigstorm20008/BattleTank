#pragma once

#include <string>


#include "GraficsComponent.h"
#include "SpriteSheet.h"

class TargetPointer :
	public GraficsComponent
{
public:
	TargetPointer(Grafics2D& gfx);
	~TargetPointer();

	void update(GameObject* gameobject)override;
	void render()override;

private:
	SpriteSheet* m_pTargetPointer;
	D2D1_POINT_2F m_gameObjectPosition;
	D2D1_POINT_2F m_mousePosition;
};

