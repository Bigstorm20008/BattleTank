#pragma once


#include "DirectXMath.h"


class GraficsComponent;
#include "GraficsComponent.h"


class GameObject
{
public:
	GameObject(GraficsComponent* graficsComponent);
	virtual~GameObject();

	virtual void update() = 0;
	DirectX::XMVECTOR& getAcceleraton();
	DirectX::XMVECTOR& getPosition();
protected:

	DirectX::XMVECTOR m_Position;  //center of mass
	DirectX::XMVECTOR m_Speed;
	DirectX::XMVECTOR m_Acceleration;

	int m_Durability;

	GraficsComponent* m_graficsComponent;
};

