#include "Window.h"


Window::Window(TCHAR* szClassName, TCHAR* szWindowName)
{
	size_t len = _tcslen(szClassName)+1;
	m_szClassName = new TCHAR[len];
	memset(m_szClassName, 0, len*sizeof(TCHAR));
	_tcscpy_s(m_szClassName, len, szClassName);

	len = _tcslen(szWindowName) + 1;
	m_szWindowName = new TCHAR[len];
	memset(m_szWindowName, 0, len*sizeof(TCHAR));
	_tcscpy_s(m_szWindowName, len, szWindowName);

	WNDCLASSEX wcex;
	wcex.cbClsExtra = wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = NULL;
	wcex.hInstance = reinterpret_cast<HINSTANCE>(GetWindowLongPtr(NULL, GWLP_HINSTANCE));
	wcex.lpfnWndProc = WindowProc;
	wcex.lpszClassName = m_szClassName;
	wcex.lpszMenuName = NULL;
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wcex);
}


Window::~Window()
{
	if (m_szClassName)
	{
		delete[]m_szClassName;
		m_szClassName = nullptr;
	}
	if (m_szWindowName)
	{
		delete[]m_szWindowName;
		m_szWindowName = nullptr;
	}
	//DestroyWindow(m_Hwnd);
}

BOOL Window::createWindow(HWND parent, UINT style, int xPos, int yPos, int width, int height)
{
	m_parentWindow = parent;
	m_width = width;
	m_height = height;
	m_xPos = xPos;
	m_yPos = yPos;
	m_Hwnd = CreateWindow(m_szClassName,
		                  m_szWindowName,
						  style,
						  xPos,yPos,
						  width,height,
						  parent,
						  NULL,
						  reinterpret_cast<HINSTANCE>(GetWindowLongPtr(NULL, GWLP_HINSTANCE)),
						  this);
	if (m_Hwnd)
	{
		//UpdateLayeredWindow(m_Hwnd, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ULW_COLORKEY);
		
		return TRUE;
	}
	else
		return FALSE;

}

HWND Window::getHandle() const
{
	return m_Hwnd;
}

void Window::move(int xPos, int yPos)
{
	if (MoveWindow(m_Hwnd, xPos, yPos, m_width, m_height, TRUE))
	{
		m_xPos = xPos;
		m_yPos = yPos;
	}
}

void Window::changeSize(int width, int height)
{
	if (MoveWindow(m_Hwnd, m_xPos, m_yPos, width, height, TRUE))
	{
		m_width = width;
		m_height = height;
	}
}

int Window::getWidth() const
{
	return m_width;
}
int Window::getHeight() const
{
	return m_height;
}
LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CREATE:
		{
			LPCREATESTRUCT lpcs;
			lpcs = (LPCREATESTRUCT)lParam;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)lpcs->lpCreateParams);
			return 0;
		}
	
		default:
		{
			Window* window = NULL;
			window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

			if (window != NULL)
			{
				return window->RealWindowProc(hWnd, msg, wParam, lParam);
			}
			else
			{
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}
		}

	}
}



