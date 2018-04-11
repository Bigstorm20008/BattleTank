#pragma once

class PlayerTankInputComponent;
class TankGraficsComponent;

#include "GameObject.h"
#include "TankGraficsComponent.h"
#include "PlayerTankInputComponent.h"

class PlayerTank :
	public GameObject
{
public:
	PlayerTank(TankGraficsComponent* tankGrafics, PlayerTankInputComponent* inputComponent);
	virtual ~PlayerTank();

	void update() override;
	float& getCurrentBodyAngle();
	float& getCurrentTowerAngle();
	DirectX::XMVECTOR& getCannonDirection();

private:
	PlayerTankInputComponent* m_input;
	float m_bodyRotationAngle;
	float m_bodyAngle;

	float m_towerRotationAngle;
	float m_towerAngle;
	DirectX::XMVECTOR m_cannonDirecton;
};

