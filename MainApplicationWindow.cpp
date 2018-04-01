#include "MainApplicationWindow.h"


MainApplicationWindow::MainApplicationWindow(TCHAR* szClassName, TCHAR* szWindowName)
	: Window(szClassName, szWindowName)
{

	createWindow(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 30, 1280, 1024);
	m_game = new Game;

	if (!m_game->initalize(this->getHandle()))
	{
		delete m_game;
		m_game = nullptr;
	}
}


MainApplicationWindow::~MainApplicationWindow()
{
	DestroyWindow(this->getHandle());
}


LRESULT MainApplicationWindow::RealWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	
		case WM_DESTROY:
		{		
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}