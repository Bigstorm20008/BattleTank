#pragma once

#include "Window.h"


class MainApplicationWindow :
	public Window
{
public:
	MainApplicationWindow(TCHAR* szClassName, TCHAR* szWindowName);
	~MainApplicationWindow();
private:
	virtual LRESULT RealWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

