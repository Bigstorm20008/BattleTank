#pragma once

#include "Window.h"
#include "Game.h"

class MainApplicationWindow :
	public Window
{
public:
	MainApplicationWindow(TCHAR* szClassName, TCHAR* szWindowName);
	~MainApplicationWindow();
private:
	Game* m_game;


	virtual LRESULT RealWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

