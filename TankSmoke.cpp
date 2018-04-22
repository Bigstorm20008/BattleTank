#include "TankSmoke.h"


TankSmoke::TankSmoke(Grafics2D& gfx) : GraficsComponent(gfx)
{
	m_animatedSmoke = new SpriteSheet;
	m_animatedSmoke->initialize(L"Resources\\BattleTank\\1.PNG", 100, m_pGfx);
	m_spriteAngle = 0;
	m_isPlayed = true;
}


TankSmoke::~TankSmoke()
{
	if (m_animatedSmoke)
	{
		delete m_animatedSmoke;
		m_animatedSmoke = nullptr;
	}
}

void TankSmoke::update(GameObject* gameobject)
{
	if (m_animatedSmoke->currentFrame > 99)
	{
		m_isPlayed = false;
		return;
	}
	m_animatedSmoke->setTransformation(m_rotationMatrix*m_translationMatrix);
	m_animatedSmoke->animate();
	

	/*DirectX::XMVECTOR position = gameobject->getPosition();
	float tankBodyAngle = static_cast<PlayerTank*>(gameobject)->getCurrentBodyAngle();
	
	DirectX::XMFLOAT2 transSize;
	DirectX::XMStoreFloat2(&transSize, position);
	transSize.y += 55;
	D2D1::Matrix3x2F translationMatrix = D2D1::Matrix3x2F::Translation(D2D1::SizeF(transSize.x - 100 / 2, transSize.y - m_animatedSmoke->getHeight() / 2));
	if (m_spriteAngle != tankBodyAngle)
	{
		D2D1::Matrix3x2F bodyRotationMatrix = D2D1::Matrix3x2F::Rotation(tankBodyAngle, D2D1::Point2F(100/2,-35));
		m_animatedSmoke->setTransformation(bodyRotationMatrix*translationMatrix);
		m_spriteAngle = tankBodyAngle;
	}
	else
	{
		D2D1::Matrix3x2F bodyRotationMatrix = D2D1::Matrix3x2F::Rotation(m_spriteAngle, D2D1::Point2F(100 / 2, -35));
		m_animatedSmoke->setTransformation(bodyRotationMatrix*translationMatrix);
	}*/

	
}

void TankSmoke::render()
{
	m_animatedSmoke->draw();
}

TankSmoke* TankSmoke::copy()
{
	return new TankSmoke(*m_pGfx);
}


void TankSmoke::setTranslation(float x, float y)
{
	m_translationMatrix = D2D1::Matrix3x2F::Translation(D2D1::SizeF(x - 100 / 2, y - m_animatedSmoke->getHeight() / 2));
}

void TankSmoke::setRotation(float angle)
{
	m_rotationMatrix = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(100 / 2, 0));
}

bool TankSmoke::isPlayed()
{
	return m_isPlayed;
}