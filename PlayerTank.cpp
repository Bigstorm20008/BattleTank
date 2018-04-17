#include "PlayerTank.h"


PlayerTank::PlayerTank(TankGraficsComponent* tankGrafics, PlayerTankInputComponent* inputComponent) : GameObject(tankGrafics)
{
	m_input = inputComponent;
	m_graficsComponent = tankGrafics;
	m_Acceleration = m_Speed = DirectX::XMVectorSet(0.f, 1.f, 0.f, 0.f);
	m_cannonDirecton = DirectX::XMVectorSet(0.f, -1.f, 0.f, 0.f);
	m_Position = DirectX::XMVectorSet(0.f, 0.f, 0.f, 0.f);
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
}

void PlayerTank::render()
{
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
