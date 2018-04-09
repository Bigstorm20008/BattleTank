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
}


void TankGraficsComponent::update(GameObject* gameObject)
{
	DirectX::XMVECTOR position = gameObject->getPosition();
	DirectX::XMVECTOR acceleration = gameObject->getAcceleraton();
	float tankBodyAngle = static_cast<PlayerTank*>(gameObject)->getCurrentBodyAngle();

	DirectX::XMFLOAT2 transSize;
	DirectX::XMStoreFloat2(&transSize, position);
	D2D1::Matrix3x2F translationMatrix = D2D1::Matrix3x2F::Translation(D2D1::SizeF(transSize.x, transSize.y));
	D2D1::Matrix3x2F rotationMatrix = D2D1::Matrix3x2F::Rotation(tankBodyAngle, D2D1::Point2F(m_pTankBody->getWidth() / 2, m_pTankBody->getHeight() / 2));
	m_pTankBody->setTransformation(rotationMatrix*translationMatrix);
	m_pTankBody->draw();
	//m_pTankTower->draw();
}
