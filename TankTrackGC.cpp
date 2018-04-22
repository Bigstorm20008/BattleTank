#include "TankTrackGC.h"


TankTrackGC::TankTrackGC(Grafics2D& gfx) :GraficsComponent(gfx)
{
	m_trackSprite = new SpriteSheet;
	wchar_t* pointerLocation = L"Resources\\BattleTank\\tracks.PSD";
	m_trackSprite->initialize(pointerLocation, m_pGfx);
}


TankTrackGC::~TankTrackGC()
{
	if (m_trackSprite)
	{
		delete m_trackSprite;
		m_trackSprite = nullptr;
	}
}


void TankTrackGC::update(GameObject* gameobject)
{
	m_trackSprite->setTransformation(m_rotationMatrix * m_translationMatrix);
}

void TankTrackGC::render()
{
	m_trackSprite->draw();
}

void TankTrackGC::setPositon(DirectX::XMVECTOR& position)
{
	m_Postion = position;
	DirectX::XMFLOAT2 transSize;
	DirectX::XMStoreFloat2(&transSize, position);
	m_translationMatrix = D2D1::Matrix3x2F::Translation(D2D1::SizeF(transSize.x - m_trackSprite->getWidth() / 2, transSize.y ));
}
DirectX::XMVECTOR& TankTrackGC::getPosition()
{
	return m_Postion;
}

int TankTrackGC::getHeight()
{
	return m_trackSprite->getHeight();
}


TankTrackGC* TankTrackGC::copy()
{
	TankTrackGC* trackCopy = new TankTrackGC(*m_pGfx);
	return trackCopy;
}

void TankTrackGC::setAngle(float& angle)
{
	m_spriteAngle = angle;
	m_rotationMatrix = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(m_trackSprite->getWidth() / 2, m_trackSprite->getHeight() / 2));
}