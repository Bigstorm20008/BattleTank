#pragma once

#include "GraficsComponent.h"
#include "PlayerTank.h"
#include "SpriteSheet.h"


class TankSmoke :
	public GraficsComponent
{
public:
	TankSmoke(Grafics2D& gfx);
	~TankSmoke();

	void update(GameObject* gameobject)override;
	void render()override;

	void setTranslation(float x,float y);
	void setRotation(float angle);
	bool isPlayed();

	TankSmoke* copy();
private:
	float m_spriteAngle;
	SpriteSheet* m_animatedSmoke;

	bool m_isPlayed;
	D2D1::Matrix3x2F m_translationMatrix;
	D2D1::Matrix3x2F m_rotationMatrix;
};

