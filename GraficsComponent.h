#pragma once

#include "Grafics2D.h"
class GameObject;
#include "GameObject.h"

class GraficsComponent
{
public:
	GraficsComponent(Grafics2D& gfx);
	virtual ~GraficsComponent();
	virtual void update(GameObject* gameobject) = 0;
	virtual void render() = 0;
protected:
	Grafics2D* m_pGfx;
};

