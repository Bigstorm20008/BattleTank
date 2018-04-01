#pragma once

#include "Grafics2D.h"
#include "SpriteSheet.h"

class Game
{
public:
	Game();
	virtual ~Game();

	bool initalize(HWND gameWindow);

	LRESULT messageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
	HWND m_gameWindow;
	Grafics2D* m_gfx;


	SpriteSheet* m_playerTank;
	void freeAllResources();
};

