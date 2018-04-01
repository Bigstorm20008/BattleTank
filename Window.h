#pragma once

#include <Windows.h>
#include <tchar.h>

class Window
{
public:

	Window(TCHAR* szClassName, TCHAR* szWindowName);
	~Window();
	
	BOOL createWindow(HWND parent, UINT style, int xPos, int yPos, int width, int height);
	HWND getHandle() const;
	void move(int xPos, int yPos);
	void changeSize(int width, int height);
	int getWidth() const;
	int getHeight() const;
private:
	HWND m_Hwnd;
	HWND m_parentWindow;
	TCHAR* m_szClassName;
	TCHAR* m_szWindowName;
	int m_width;
	int m_height;
	int m_xPos;
	int m_yPos;

	inline BOOL registerWindowClass();
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:

	
	virtual LRESULT RealWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;
	
};

