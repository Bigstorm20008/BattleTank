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
}
