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


	PlayerTank* m_pPlayerTank;
	SpriteSheet* m_explosion;
	void intGameObjects();

	void freeAllResources();
};

