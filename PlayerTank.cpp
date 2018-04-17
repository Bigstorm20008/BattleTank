#include "PlayerTank.h"


PlayerTank::PlayerTank(TankGraficsComponent* tankGrafics, PlayerTankInputComponent* inputComponent, TargetPointer* targetPointer) : GameObject(tankGrafics)
{
	m_input = inputComponent;
	m_graficsComponent = tankGrafics;
	m_targetPointer = targetPointer;
	m_Acceleration = m_Speed = DirectX::XMVectorSet(0.f, 1.f, 0.f, 0.f);
	m_cannonDirecton = DirectX::XMVectorSet(0.f, -1.f, 0.f, 0.f);

	int bodySpriteWidth, bodySpriteHeight;
	bodySpriteWidth = tankGrafics->getBodyWidth();
	bodySpriteHeight = tankGrafics->getBodyHeight();

	m_Position = DirectX::XMVectorSet(bodySpriteWidth/2, bodySpriteHeight/2, 0.f, 0.f);
	m_bodyRotationAngle = 3;
	m_bodyAngle = 0;

	m_towerAngle = 0;
}


PlayerTank::~PlayerTank()
{
}


void PlayerTank::update()
{
	m_input->update(this);
	m_graficsComponent->update(this);
	m_targetPointer->update(this);
}

void PlayerTank::render()
{
	m_targetPointer->render();
	m_graficsComponent->render();
}

float& PlayerTank::getCurrentBodyAngle()
{
	return m_bodyAngle;
}

float& PlayerTank::getCurrentTowerAngle()
{
	return m_towerAngle;
}

DirectX::XMVECTOR& PlayerTank::getCannonDirection()
{
	return m_cannonDirecton;
}

void PlayerTank::setTankPosition(int xPos, int yPos)
{
	m_Position = DirectX::XMVectorSet(xPos - static_cast<TankGraficsComponent*>(m_graficsComponent)->getBodyWidth() / 2, yPos - static_cast<TankGraficsComponent*>(m_graficsComponent)->getBodyHeight()/2, 0.f, 0.f);
}
