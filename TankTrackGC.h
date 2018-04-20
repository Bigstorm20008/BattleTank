#pragma once

#include "GraficsComponent.h"
#include "SpriteSheet.h"
#include "PlayerTank.h"

class TankTrackGC :
	public GraficsComponent
{
public:
	TankTrackGC(Grafics2D& gfx);
	~TankTrackGC();

	void update(GameObject* gameobject)override;
	void render()override;

	TankTrackGC* copy();
	void setPositon(DirectX::XMVECTOR& position);
	void setAngle(float& angle);
	DirectX::XMVECTOR& getPosition();
	int getHeight();
private:
	SpriteSheet* m_trackSprite;
	DirectX::XMVECTOR m_Postion;
	float m_spriteAngle;
	D2D1::Matrix3x2F m_translationMatrix;
	D2D1::Matrix3x2F m_rotationMatrix;
	bool m_isVisible;
	int m_lifeTime;

};

