#pragma once

#include <wincodec.h>
#include "DirectXMath.h"
#include "D2d1_1helper.h"
#include "Grafics2D.h"

class SpriteSheet
{
public:
	SpriteSheet();
	virtual ~SpriteSheet();

	bool initialize(wchar_t* fileLocation, float frameWidth, Grafics2D* gfx);
	void draw();
	void animate();
	
	float getWidth() const;
	float getHeight() const;
	void setTransformation(D2D1::Matrix3x2F& transformMatrix);
	void drawVector(DirectX::XMVECTOR v, int lenght = 1);
	void drawText(WCHAR* text, int size);
	int currentFrame;
protected:
	float m_frameWidth;
	Grafics2D* m_pGfx;
	ID2D1Bitmap* m_pBitmap;
	D2D1::Matrix3x2F m_transformationMatrix;
	D2D1_RECT_F m_positionInWindow;
	D2D1_RECT_F m_positionInSpriteSheet;
	
private:
	IWICImagingFactory* m_pWicFactory;
	IWICBitmapDecoder* m_pWicDecoder;
	IWICBitmapFrameDecode* m_pWicFrameDecode;
	IWICFormatConverter* m_pWicConverter;

	void releaseWicResources();
};

