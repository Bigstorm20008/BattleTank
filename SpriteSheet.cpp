#include "SpriteSheet.h"


SpriteSheet::SpriteSheet()
{
	
}


SpriteSheet::~SpriteSheet()
{
}


bool SpriteSheet::initialize(wchar_t* fileLocation, float frameWidth, Grafics2D* gfx)
{
	m_pGfx = gfx;

	if (!m_pGfx)
	{
		MessageBox(NULL, L"Не указан графический ускоритель", L"Ошибка инициализации класс SpriteSheet", MB_OK);
		return false;
	}

	m_frameWidth = frameWidth;
	
	m_rotationMatrix = D2D1::Matrix3x2F::Rotation(0, D2D1::Point2F(0.f, 0.f));
	m_translationMatrix = D2D1::Matrix3x2F::Translation(D2D1::SizeF(0.f, 0.f));

	HRESULT hResult;

	hResult = CoCreateInstance(CLSID_WICImagingFactory,
		                       NULL,
		                       CLSCTX_INPROC_SERVER,
		                       IID_IWICImagingFactory,
		                       (LPVOID*)&m_pWicFactory);
	if (hResult != S_OK)
	{
		MessageBox(NULL, L"Не удалось создать WicFactory", L"Ошибка инициализации класс SpriteSheet", MB_OK);
		releaseWicResources();
		return false;
	}

	hResult = m_pWicFactory->CreateDecoderFromFilename(fileLocation,
			                                        NULL,
			                                        GENERIC_READ,
			                                        WICDecodeMetadataCacheOnLoad,
	   	                                            &m_pWicDecoder);
	if (hResult != S_OK)
	{
		MessageBox(NULL, L"Не удалось создать WicDecoder", L"Ошибка инициализации класс SpriteSheet", MB_OK);
		releaseWicResources();
		return false;
	}

	
	hResult = m_pWicDecoder->GetFrame(0, &m_pWicFrameDecode);
	if (hResult != S_OK)
	{
		MessageBox(NULL, L"Не удалось создать WicFrameDecode", L"Ошибка инициализации класс SpriteSheet", MB_OK);
		releaseWicResources();
		return false;
	}

	hResult = m_pWicFactory->CreateFormatConverter(&m_pWicConverter);
	if (hResult != S_OK)
	{
		MessageBox(NULL, L"Не удалось создать WicConverter", L"Ошибка инициализации класс SpriteSheet", MB_OK);
		releaseWicResources();
		return false;
	}

	
	
	hResult = m_pWicConverter->Initialize(m_pWicFrameDecode,
			                              GUID_WICPixelFormat32bppPBGRA,
			                              WICBitmapDitherTypeNone,
			                              NULL,
			                              0.0f,
			                              WICBitmapPaletteTypeCustom);
	if (hResult != S_OK)
	{
		MessageBox(NULL, L"Не удалось инициализировать WicConverter", L"Ошибка инициализации класс SpriteSheet", MB_OK);
		releaseWicResources();
		return false;
	}
	
	ID2D1HwndRenderTarget* renderTarget = m_pGfx->getRenderTarget();
	if (!renderTarget)
	{
		MessageBox(NULL, L"Не удалось получить RenderTarget", L"Ошибка инициализации класс SpriteSheet", MB_OK);
		releaseWicResources();
		return false;
	}

	hResult = (renderTarget->CreateBitmapFromWicBitmap(m_pWicConverter, NULL, &m_pBitmap));
	if (hResult != S_OK)
	{
		MessageBox(NULL, L"Не удалось создать Bitmap", L"Ошибка инициализации класс SpriteSheet", MB_OK);
		releaseWicResources();
		return false;
	}


	m_positionInWindow.left = 0.f;
	m_positionInWindow.top = 0.f;
	m_positionInWindow.right = m_frameWidth;
	m_positionInWindow.bottom = m_pBitmap->GetSize().height;

	m_positionInSpriteSheet.left = 0.f;
	m_positionInSpriteSheet.top = 0.f;
	m_positionInSpriteSheet.right = m_frameWidth;
	m_positionInSpriteSheet.bottom = m_pBitmap->GetSize().height;

	releaseWicResources();

	return true;
}

void SpriteSheet::releaseWicResources()
{
	if (m_pWicFactory)
	{
		m_pWicFactory->Release();
		m_pWicFactory = NULL;
	}
	if (m_pWicDecoder)
	{
		m_pWicDecoder->Release();
		m_pWicDecoder = NULL;
	}
	if (m_pWicConverter)
	{
		m_pWicConverter->Release();
		m_pWicConverter = NULL;
	}
	if (m_pWicFrameDecode)
	{
		m_pWicFrameDecode->Release();
		m_pWicFrameDecode = NULL;
	}
}
