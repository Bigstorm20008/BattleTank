#include "Grafics2D.h"


Grafics2D::Grafics2D()
{
	m_pFactory = nullptr;
	m_pRenderTarget = nullptr;
	m_pSolidColorBrush = nullptr;
}


Grafics2D::~Grafics2D()
{
	releaseAll();
}

bool Grafics2D::init(HWND windowForDirect2D)
{
	HRESULT result = S_OK;

	result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);

	if (result != S_OK)
	{
		releaseAll();
		return false;
	}

	RECT rc;
	GetWindowRect(windowForDirect2D, &rc);
    result = m_pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		                                        D2D1::HwndRenderTargetProperties(windowForDirect2D, D2D1::SizeU(rc.right, rc.bottom)),
												&m_pRenderTarget);
	if (result != S_OK)
	{
		releaseAll();
		return false;
	}

	result = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.f, 0.f, 0.f), &m_pSolidColorBrush);
	if (result != S_OK)
	{
		releaseAll();
		return false;
	}

	return true;
}


void Grafics2D::releaseAll()
{
	if (m_pFactory)
	{
		m_pFactory->Release();
		m_pFactory = nullptr;
	}
	if (m_pRenderTarget)
	{
		m_pRenderTarget->Release();
		m_pRenderTarget = nullptr;
	}
	if (m_pSolidColorBrush)
	{
		m_pSolidColorBrush->Release();
		m_pSolidColorBrush = nullptr;

	}
}

void Grafics2D::beginDraw()
{
	m_pRenderTarget->BeginDraw();
}

void Grafics2D::endDraw()
{
	m_pRenderTarget->EndDraw();
}

void Grafics2D::clearScreen(float red, float green, float blue)
{
	m_pRenderTarget->Clear(D2D1::ColorF(red, green, blue));
}
