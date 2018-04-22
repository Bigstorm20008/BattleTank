#pragma once

#include <vector>

#include "Grafics2D.h"
#include "SpriteSheet.h"
#include "PlayerTank.h"


class Game
{
public:
	Game();
	virtual ~Game();

	bool initalize(HWND gameWindow);
	void update();
	void render();
	void explosion();

protected:
	HWND m_gameWindow;
	Grafics2D* m_gfx;

	SpriteSheet* m_background;
	PlayerTank* m_pPlayerTank;
	SpriteSheet* m_explosion;
	
	//PlayerTank Components
	PlayerTankInputComponent* m_playerInput;
	TankGraficsComponent* m_playerTankGrafics;
	TargetPointer* m_targetPonter;
	TankTrackGC* m_tankTrack;
	TankSmoke* m_smoke;

	void initInputComponents();
	void initGraficsComponents();
	void initPhysicsComponents();
	void initGameWorld();
	void initGameObjects();

	void freeAllResources();
};

