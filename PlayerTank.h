#pragma once

#include <vector>
#include <chrono>
#include <random>
#include <ctime>

class PlayerTankInputComponent;
class TankGraficsComponent;
class TankTrackGC;
class TankSmoke;

#include "GameObject.h"
#include "TankGraficsComponent.h"
#include "PlayerTankInputComponent.h"
#include "TargetPointer.h"
#include "TankTrackGC.h"
#include "TankSmoke.h"
#include "SoundEngine.h"
#include "SoundFactory.h"

class PlayerTank :
	public GameObject
{
public:
	PlayerTank(TankGraficsComponent* tankGrafics, PlayerTankInputComponent* inputComponent, TargetPointer* targetPointer, TankTrackGC* tankTrack, TankSmoke* smoke, SoundEngine* soundEngine);
	virtual ~PlayerTank();

	void update() override;
	void render() override;

	float& getCurrentBodyAngle();
	float& getCurrentTowerAngle();
	std::vector<TankTrackGC*>& getTankTracks();
	std::vector<TankSmoke*>& getTankSmokes();
	DirectX::XMVECTOR& getCannonDirection();

	void setTankPosition(int xPos, int yPos);
	enum TankStates{ tankWait, tankMoving } m_tankState;
private:
	PlayerTankInputComponent* m_input;
	TargetPointer* m_targetPointer;
	TankSmoke* m_smoke;

	std::vector<TankTrackGC*> m_tankTracks;

	


	std::vector<TankSmoke*> m_tankSmokes;
	std::chrono::high_resolution_clock::time_point m_currentTimePoint;
	std::chrono::high_resolution_clock::time_point m_previousTimePoint;

	float m_bodyRotationAngle;
	float m_bodyAngle;

	float m_towerRotationAngle;
	float m_towerAngle;
	DirectX::XMVECTOR m_cannonDirecton;

	void updateSmoke();

	Sound* m_tankWaitSound;
	Sound* m_tankMovingSound;
};

