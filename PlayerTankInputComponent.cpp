#include "PlayerTankInputComponent.h"


PlayerTankInputComponent::PlayerTankInputComponent()
{
}


PlayerTankInputComponent::~PlayerTankInputComponent()
{
}

void PlayerTankInputComponent::update(GameObject* gameObject)
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		DirectX::XMVECTOR& acceleration = gameObject->getAcceleraton();			
		DirectX::XMMATRIX rotationAroundZ = DirectX::XMMatrixRotationZ(-0.5f*DirectX::XM_PI / 180);
		acceleration = DirectX::XMVector2Transform(acceleration, rotationAroundZ);
		float& currentBodyAngle = static_cast<PlayerTank*>(gameObject)->getCurrentBodyAngle();
		if (currentBodyAngle == 0)
			currentBodyAngle = 360;
		currentBodyAngle -= 0.5f;

		DirectX::XMVECTOR& cannonDirection = static_cast<PlayerTank*>(gameObject)->getCannonDirection();
		cannonDirection = DirectX::XMVector2Transform(cannonDirection, rotationAroundZ);
		float& currentTowerAngle = static_cast<PlayerTank*>(gameObject)->getCurrentTowerAngle();
		if (currentTowerAngle == 0)
			currentTowerAngle = 360;
		currentTowerAngle -= 0.5f;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		DirectX::XMVECTOR& acceleration = gameObject->getAcceleraton();
		DirectX::XMMATRIX rotationAroundZ = DirectX::XMMatrixRotationZ(0.5f * DirectX::XM_PI / 180);
		acceleration = DirectX::XMVector2Transform(acceleration, rotationAroundZ);
		float& currentBodyAngle = static_cast<PlayerTank*>(gameObject)->getCurrentBodyAngle();
		if (currentBodyAngle == 360)
			currentBodyAngle = 0;
		currentBodyAngle += 0.5f;

		DirectX::XMVECTOR& cannonDirection = static_cast<PlayerTank*>(gameObject)->getCannonDirection();
		cannonDirection = DirectX::XMVector2Transform(cannonDirection, rotationAroundZ);
		float& currentTowerAngle = static_cast<PlayerTank*>(gameObject)->getCurrentTowerAngle();
		if (currentTowerAngle == 360)
			currentTowerAngle = 0;
		currentTowerAngle += 0.5f;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		DirectX::XMVECTOR& acceleration = gameObject->getAcceleraton();
		DirectX::XMVECTOR& position = gameObject->getPosition();
		position = DirectX::XMVectorSubtract(position, acceleration);	
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		DirectX::XMVECTOR& acceleration = gameObject->getAcceleraton();
		DirectX::XMVECTOR& position = gameObject->getPosition();
		position = DirectX::XMVectorAdd(position, acceleration);
	}

	auto& tracks = static_cast<PlayerTank*>(gameObject)->getTankTracks();
	int lastTrack = tracks.size() - 1;
	DirectX::XMVECTOR& position = gameObject->getPosition();
	DirectX::XMVECTOR vec =  DirectX::XMVectorSubtract(position, tracks[lastTrack]->getPosition());
	DirectX::XMVECTOR vecLenght = DirectX::XMVector2Length(vec);
	if (DirectX::XMVectorGetX(vecLenght) > tracks[lastTrack]->getHeight())
	{
		TankTrackGC* track = tracks[lastTrack]->copy();
		track->setPositon(position);
		float angle = static_cast<PlayerTank*>(gameObject)->getCurrentBodyAngle();
		track->setAngle(angle);
		tracks.push_back(track);
	}


	POINT mousePosition;
	GetCursorPos(&mousePosition);
	HWND gameWindow = FindWindow(L"MainApplicationWindow", L"Battle Tank");
	ScreenToClient(gameWindow, &mousePosition);

	DirectX::XMVECTOR vectorMousePosition = DirectX::XMVectorSet(static_cast<FLOAT>(mousePosition.x), static_cast<FLOAT>(mousePosition.y), 0.f, 0.f);
	//DirectX::XMVECTOR position = gameObject->getPosition();

	DirectX::XMVECTOR directionToMousePosition = DirectX::XMVectorSubtract(vectorMousePosition, position);
	DirectX::XMVECTOR directionToMousePositionNorm = DirectX::XMVector2Normalize(directionToMousePosition);
    
	DirectX::XMVECTOR& cannonDirection = static_cast<PlayerTank*>(gameObject)->getCannonDirection();

	DirectX::XMVECTOR angle = DirectX::XMVector2AngleBetweenVectors(cannonDirection, directionToMousePositionNorm);
	float angleInDigrees = DirectX::XMConvertToDegrees(DirectX::XMVectorGetX(angle));
	
	float& tankTowerAngle = static_cast<PlayerTank*>(gameObject)->getCurrentTowerAngle();

	if (angleInDigrees == 180)
	{
		return;
	}

	DirectX::XMVECTOR crossProduct = DirectX::XMVector2Cross(cannonDirection, directionToMousePositionNorm);
	if (angleInDigrees < 180)
	{
		if (DirectX::XMVectorGetX(crossProduct) < 0)
		{
			if (angleInDigrees > 0.25f)
			{
				DirectX::XMMATRIX rotationAroundZ = DirectX::XMMatrixRotationZ(-0.25f * DirectX::XM_PI / 180);
				cannonDirection = DirectX::XMVector2Transform(cannonDirection, rotationAroundZ);
				tankTowerAngle -= 0.25;
			}
			else
			{
				DirectX::XMMATRIX rotationAroundZ = DirectX::XMMatrixRotationZ(-angleInDigrees * DirectX::XM_PI / 180);
				cannonDirection = DirectX::XMVector2Transform(cannonDirection, rotationAroundZ);
				tankTowerAngle -= angleInDigrees;
			}
		}
		if (DirectX::XMVectorGetX(crossProduct) > 0)
		{
			if (angleInDigrees > 0.25f)
			{
				DirectX::XMMATRIX rotationAroundZ = DirectX::XMMatrixRotationZ(0.25f * DirectX::XM_PI / 180);
				cannonDirection = DirectX::XMVector2Transform(cannonDirection, rotationAroundZ);
				tankTowerAngle += 0.25;
			}
			else
			{
				DirectX::XMMATRIX rotationAroundZ = DirectX::XMMatrixRotationZ(angleInDigrees * DirectX::XM_PI / 180);
				cannonDirection = DirectX::XMVector2Transform(cannonDirection, rotationAroundZ);
				tankTowerAngle += angleInDigrees;
			}
		}

	}
	
}
