#include "MainApplicationWindow.h"


MainApplicationWindow::MainApplicationWindow(TCHAR* szClassName, TCHAR* szWindowName)
	: Window(szClassName, szWindowName)
{

	createWindow(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 1280, 1024);
	
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
		default:
			break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}