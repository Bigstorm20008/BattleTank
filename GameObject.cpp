#include "GameObject.h"


GameObject::GameObject(GraficsComponent* graficsComponent)
{
	m_graficsComponent = graficsComponent;
}


GameObject::~GameObject()
{
}

DirectX::XMVECTOR& GameObject::getAcceleraton()
{
	return m_Acceleration;
}

DirectX::XMVECTOR& GameObject::getPosition()
{
	return m_Position;
}
