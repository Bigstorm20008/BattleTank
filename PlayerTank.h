#pragma once

class PlayerTankInputComponent;
class TankGraficsComponent;

#include "GameObject.h"
#include "TankGraficsComponent.h"
#include "PlayerTankInputComponent.h"
#include "TargetPointer.h"

class PlayerTank :
	public GameObject
{
public:
	PlayerTank(TankGraficsComponent* tankGrafics, PlayerTankInputComponent* inputComponent, TargetPointer* targetPointer);
	virtual ~PlayerTank();

	void update() override;
	void render() override;

	float& getCurrentBodyAngle();
	float& getCurrentTowerAngle();
	DirectX::XMVECTOR& getCannonDirection();

	void setTankPosition(int xPos, int yPos);

private:
	PlayerTankInputComponent* m_input;
	TargetPointer* m_targetPointer;
	float m_bodyRotationAngle;
	float m_bodyAngle;

	float m_towerRotationAngle;
	float m_towerAngle;
	DirectX::XMVECTOR m_cannonDirecton;
};

