#include "TankGraficsComponent.h"


TankGraficsComponent::TankGraficsComponent(Grafics2D& gfx) : GraficsComponent(gfx)
{
}


TankGraficsComponent::~TankGraficsComponent()
{
	if (m_pTankBody)
	{
		delete m_pTankBody;
		m_pTankBody = nullptr;
	}
	if (m_pTankTower)
	{
		delete m_pTankTower;
		m_pTankTower = nullptr;
	}
}


void TankGraficsComponent::initComponent(wchar_t& tankBodyFileLocation, wchar_t& tankTowerFileLocation, float spriteFrameWidth)
{
	m_pTankBody = new SpriteSheet;
	m_pTankBody->initialize(&tankBodyFileLocation, spriteFrameWidth, m_pGfx);

	m_pTankTower = new SpriteSheet;
	m_pTankTower->initialize(&tankTowerFileLocation, spriteFrameWidth, m_pGfx);
	D2D1::Matrix3x2F translationMatrix = D2D1::Matrix3x2F::Translation(D2D1::SizeF(0, 15));
	m_pTankTower->setTransformation(translationMatrix);
}


void TankGraficsComponent::update(GameObject* gameObject)
{
	DirectX::XMVECTOR position = gameObject->getPosition();
	DirectX::XMVECTOR acceleration = gameObject->getAcceleraton();
	float tankBodyAngle = static_cast<PlayerTank*>(gameObject)->getCurrentBodyAngle();

	DirectX::XMFLOAT2 transSize;
	DirectX::XMStoreFloat2(&transSize, position);
	D2D1::Matrix3x2F translationMatrix = D2D1::Matrix3x2F::Translation(D2D1::SizeF(transSize.x, transSize.y));
	D2D1::Matrix3x2F bodyRotationMatrix = D2D1::Matrix3x2F::Rotation(tankBodyAngle, D2D1::Point2F(m_pTankBody->getWidth() / 2, m_pTankBody->getHeight() / 2));
	m_pTankBody->setTransformation(bodyRotationMatrix*translationMatrix);


	float tankTowerAngle = static_cast<PlayerTank*>(gameObject)->getCurrentTowerAngle();
	D2D1::Matrix3x2F towerRotationMatrix = D2D1::Matrix3x2F::Rotation(tankTowerAngle, D2D1::Point2F(m_pTankTower->getWidth() / 2, m_pTankTower->getHeight() / 2));
	D2D1::Matrix3x2F towerTranslationMatrix = D2D1::Matrix3x2F::Translation(D2D1::SizeF(transSize.x, transSize.y + 15));
	m_pTankTower->setTransformation(towerRotationMatrix * towerTranslationMatrix);

	m_pTankBody->draw();
	m_pTankTower->draw();


	/*POINT mousePosition;
	GetCursorPos(&mousePosition);
	HWND gameWindow = FindWindow(L"MainApplicationWindow", L"Battle Tank");
	ScreenToClient(gameWindow, &mousePosition);

	DirectX::XMVECTOR vectorMousePosition = DirectX::XMVectorSet(mousePosition.x, mousePosition.y, 0.f, 0.f);
	m_pTankBody->drawVector(vectorMousePosition);

	m_pTankBody->drawVector(position);

	m_pTankBody->drawVector(DirectX::XMVectorSubtract(position, vectorMousePosition));
	DirectX::XMVECTOR direction = static_cast<PlayerTank*>(gameObject)->getCannonDirection();
	m_pTankBody->drawVector(direction,30);

	//m_pTankBody->drawVector(position);*/

	POINT mousePosition;
	GetCursorPos(&mousePosition);
	HWND gameWindow = FindWindow(L"MainApplicationWindow", L"Battle Tank");
	ScreenToClient(gameWindow, &mousePosition);

	DirectX::XMVECTOR vectorMousePosition = DirectX::XMVectorSet(mousePosition.x, mousePosition.y, 0.f, 0.f);
	
	DirectX::XMVECTOR directionToMousePosition = DirectX::XMVectorSubtract(position, vectorMousePosition);
	DirectX::XMVECTOR directionToMousePositionNorm = DirectX::XMVector2Normalize(directionToMousePosition);

	DirectX::XMVECTOR& cannonDirection = static_cast<PlayerTank*>(gameObject)->getCannonDirection();

	DirectX::XMVECTOR angle = DirectX::XMVector2AngleBetweenVectors(directionToMousePosition, cannonDirection);
	float angleInDigrees = DirectX::XMConvertToDegrees(DirectX::XMVectorGetX(angle));

	std::wstring angleD = std::to_wstring(angleInDigrees);
	m_pGfx->drawText(angleD.c_str());

	m_pTankBody->drawVector(vectorMousePosition);

	m_pTankBody->drawVector(position);
	m_pTankBody->drawVector(DirectX::XMVectorSubtract(position, vectorMousePosition));
	m_pTankBody->drawVector(cannonDirection, 30);
}
