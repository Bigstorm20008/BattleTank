#include "PlayerTank.h"


PlayerTank::PlayerTank(TankGraficsComponent* tankGrafics, PlayerTankInputComponent* inputComponent, TargetPointer* targetPointer, TankTrackGC* tankTrack, TankSmoke* smoke) : GameObject(tankGrafics)
{
	m_input = inputComponent;
	m_graficsComponent = tankGrafics;
	m_targetPointer = targetPointer;
	m_smoke = smoke;
	m_Acceleration = m_Speed = DirectX::XMVectorSet(0.f, 1.f, 0.f, 0.f);
	m_cannonDirecton = DirectX::XMVectorSet(0.f, -1.f, 0.f, 0.f);

	int bodySpriteWidth, bodySpriteHeight;
	bodySpriteWidth = tankGrafics->getBodyWidth();
	bodySpriteHeight = tankGrafics->getBodyHeight();

	m_Position = DirectX::XMVectorSet(bodySpriteWidth/2, bodySpriteHeight/2, 0.f, 0.f);
	m_bodyRotationAngle = 3;
	m_bodyAngle = 0;

	m_towerAngle = 0;

	m_tankTracks.reserve(100);
	m_tankTracks.push_back(tankTrack);

	m_tankSmokes.reserve(50);
	m_tankSmokes.push_back(m_smoke);

	m_currentTimePoint = m_previousTimePoint = std::chrono::high_resolution_clock::now();
}


PlayerTank::~PlayerTank()
{
}


void PlayerTank::update()
{
	m_input->update(this);
	m_graficsComponent->update(this);
	m_targetPointer->update(this);
	for (auto& track : m_tankTracks)
	{
		track->update(this);
	}
	updateSmoke();
}

void PlayerTank::render()
{
	m_targetPointer->render();
	

	for (auto& track : m_tankTracks)
	{
		track->render();
	}

	m_graficsComponent->render();

	for (auto& smoke : m_tankSmokes)
	{	
		smoke->render();
	}

	
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

std::vector<TankTrackGC*>& PlayerTank::getTankTracks()
{
	return m_tankTracks;
}

std::vector<TankSmoke*>& PlayerTank::getTankSmokes()
{
	return m_tankSmokes;
}

void PlayerTank::updateSmoke()
{
	m_currentTimePoint = std::chrono::system_clock::now();
	std::chrono::milliseconds miliseconds200(200);
	if (std::chrono::duration_cast<std::chrono::milliseconds>(m_currentTimePoint - m_previousTimePoint) >= miliseconds200)
	{
		DirectX::XMFLOAT2 transSize;
		DirectX::XMStoreFloat2(&transSize, m_Position);
		int lastSmoke = m_tankSmokes.size() - 1;

		TankSmoke* smoke1 = m_tankSmokes[lastSmoke]->copy();
		smoke1->setTranslation(transSize.x-6, transSize.y+50);
		smoke1->setRotation(m_bodyAngle);
		m_tankSmokes.push_back(smoke1);

		TankSmoke* smoke2 = m_tankSmokes[lastSmoke]->copy();
		smoke2->setTranslation(transSize.x + 6, transSize.y + 50);
		smoke2->setRotation(m_bodyAngle);
		m_tankSmokes.push_back(smoke2);
		m_previousTimePoint = m_currentTimePoint;
	}

	std::vector<TankSmoke*> smokeToDelete;
	smokeToDelete.reserve(30);
	
	for (auto& thisSmoke : m_tankSmokes)
	{
		if (thisSmoke->isPlayed())
		{
			thisSmoke->update(this);
		}
		else
		{
			smokeToDelete.push_back(thisSmoke);
		}
	}

	for (auto& thisSmoke : smokeToDelete)
	{
		auto pos = std::find(m_tankSmokes.begin(), m_tankSmokes.end(), thisSmoke);
		delete thisSmoke;
		thisSmoke = nullptr;
		m_tankSmokes.erase(pos);
	}

}


