#include "PlayerTank.h"


PlayerTank::PlayerTank(TankGraficsComponent* tankGrafics, PlayerTankInputComponent* inputComponent) : GameObject(tankGrafics)
{
	m_input = inputComponent;
	m_graficsComponent = tankGrafics;
	m_Acceleration = m_Speed = DirectX::XMVectorSet(0.f, 1.f, 0.f, 0.f);
	m_bodyRotationAngle = 3;
}


PlayerTank::~PlayerTank()
{
}


void PlayerTank::update()
{
	m_input->update(this);
	m_graficsComponent->update(this);
}

float& PlayerTank::getCurrentBodyAngle()
{
	return m_bodyAngle;
}
