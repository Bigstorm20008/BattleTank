#pragma once

#include <vector>

class PlayerTankInputComponent;
class TankGraficsComponent;
class TankTrackGC;

#include "GameObject.h"
#include "TankGraficsComponent.h"
#include "PlayerTankInputComponent.h"
#include "TargetPointer.h"
#include "TankTrackGC.h"

class PlayerTank :
	public GameObject
{
public:
	PlayerTank(TankGraficsComponent* tankGrafics, PlayerTankInputComponent* inputComponent, TargetPointer* targetPointer,TankTrackGC* tankTrack);
	virtual ~PlayerTank();

	void update() override;
	void render() override;

	float& getCurrentBodyAngle();
	float& getCurrentTowerAngle();
	std::vector<TankTrackGC*>& getTankTracks();
	DirectX::XMVECTOR& getCannonDirection();

	void setTankPosition(int xPos, int yPos);
	
private:
	PlayerTankInputComponent* m_input;
	TargetPointer* m_targetPointer;
	std::vector<TankTrackGC*> m_tankTracks;
	float m_bodyRotationAngle;
	float m_bodyAngle;

	float m_towerRotationAngle;
	float m_towerAngle;
	DirectX::XMVECTOR m_cannonDirecton;
};

