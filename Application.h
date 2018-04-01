#pragma once

#include "MainApplicationWindow.h"

class Application
{
public:
	Application();
	~Application();
	int run();
private:
	MainApplicationWindow* m_mainView;
	
};

