#include "WallBlockGraficsComponent.h"


WallBlockGraficsComponent::WallBlockGraficsComponent(Grafics2D& gfx) : GraficsComponent(gfx)
{
	m_WallBlockGrafics = new SpriteSheet;
	wchar_t* wallBlockSpriteLocation = L"Resources\\Wall\\wallblock.PSD";
	m_WallBlockGrafics->initialize(wallBlockSpriteLocation, 20, &gfx);
}


WallBlockGraficsComponent::~WallBlockGraficsComponent()
{
	if (m_WallBlockGrafics)
	{
		delete m_WallBlockGrafics;
		m_WallBlockGrafics = nullptr;
	}
}


void WallBlockGraficsComponent::update(GameObject* gameobject)
{

}
