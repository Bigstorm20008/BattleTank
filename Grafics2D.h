#pragma once

#include <d2d1.h>
#include "Dwrite.h"
#include <tchar.h>

class Grafics2D
{
public:
	Grafics2D();
	~Grafics2D();

	bool init(HWND windowForDirect2D);
	void beginDraw();
	void endDraw();
	void clearScreen(float red, float green, float blue);

	ID2D1HwndRenderTarget* getRenderTarget() const;

	void drawText(const WCHAR* text);
	void drawLine(D2D1_POINT_2F startPoint, D2D1_POINT_2F endPoint);
private:
	ID2D1Factory* m_pFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pSolidColorBrush;
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;

	void releaseAll();
};

