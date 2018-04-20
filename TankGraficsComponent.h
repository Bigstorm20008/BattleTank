#pragma once

#include <string>

#include "PlayerTank.h"
#include "GraficsComponent.h"
#include "SpriteSheet.h"

class TankGraficsComponent :
	public GraficsComponent
{
public:
	TankGraficsComponent(Grafics2D& gfx);
	virtual ~TankGraficsComponent();
	void initComponent(wchar_t& tankBodyFileLocation, wchar_t& tankTowerFileLocation);
	void update(GameObject* gameObject)override;
	void render() override;
	int getBodyWidth() const;
	int getBodyHeight() const;
private:
	SpriteSheet* m_pTankBody;
	SpriteSheet* m_pTankTower;
	
};

