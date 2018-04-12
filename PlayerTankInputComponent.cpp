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


	POINT mousePosition;
	GetCursorPos(&mousePosition);
	HWND gameWindow = FindWindow(L"MainApplicationWindow", L"Battle Tank");
	ScreenToClient(gameWindow, &mousePosition);

	DirectX::XMVECTOR vectorMousePosition = DirectX::XMVectorSet(mousePosition.x, mousePosition.y, 0.f, 0.f);
	DirectX::XMVECTOR position = gameObject->getPosition();

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
	if (angleInDigrees < 180)
	{
		if ((DirectX::XMVectorGetY(cannonDirection) * DirectX::XMVectorGetX(directionToMousePositionNorm) - DirectX::XMVectorGetX(cannonDirection) *DirectX::XMVectorGetY(directionToMousePositionNorm)) < 0)
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
		if ((DirectX::XMVectorGetY(cannonDirection) * DirectX::XMVectorGetX(directionToMousePositionNorm) - DirectX::XMVectorGetX(cannonDirection) *DirectX::XMVectorGetY(directionToMousePositionNorm)) > 0)
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

	}
	
}
