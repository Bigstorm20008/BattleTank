#pragma once

#include "MainApplicationWindow.h"
#include "Game.h"

class Application
{
public:
	Application();
	~Application();
	int run();
private:
	MainApplicationWindow* m_mainView;
	Game* m_pGame;
	
};

