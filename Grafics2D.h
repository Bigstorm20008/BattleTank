#pragma once

#include <d2d1.h>

class Grafics2D
{
public:
	Grafics2D();
	~Grafics2D();

	bool init(HWND windowForDirect2D);
	void beginDraw();
	void endDraw();
	void clearScreen(float red, float green, float blue);
private:
	ID2D1Factory* m_pFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pSolidColorBrush;

	void releaseAll();
};

