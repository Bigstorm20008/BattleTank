#pragma once

#include "Grafics2D.h"

class Game
{
public:
	Game();
	virtual ~Game();

	bool initalize(HWND gameWindow);
protected:
	HWND m_gameWindow;
	Grafics2D* m_gfx;

	void freeAllResources();
};

