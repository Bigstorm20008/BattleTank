#pragma once

#include <wincodec.h>

#include "Grafics2D.h"

class SpriteSheet
{
public:
	SpriteSheet();
	virtual ~SpriteSheet();

	bool initialize(wchar_t* fileLocation, float frameWidth, Grafics2D* gfx);
protected:
	float m_frameWidth;
	Grafics2D* m_pGfx;
	ID2D1Bitmap* m_pBitmap;

	D2D1_RECT_F m_positionInWindow;
	D2D1_RECT_F m_positionInSpriteSheet;
	D2D1::Matrix3x2F m_rotationMatrix;
	D2D1::Matrix3x2F m_translationMatrix;

private:
	IWICImagingFactory* m_pWicFactory;
	IWICBitmapDecoder* m_pWicDecoder;
	IWICBitmapFrameDecode* m_pWicFrameDecode;
	IWICFormatConverter* m_pWicConverter;

	void releaseWicResources();
};

