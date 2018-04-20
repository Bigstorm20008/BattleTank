#include "TargetPointer.h"


TargetPointer::TargetPointer(Grafics2D& gfx) :GraficsComponent(gfx)
{
	m_pTargetPointer = new SpriteSheet;
	wchar_t* pointerLocation = L"Resources\\BattleTank\\targetPointer.PNG";
	m_pTargetPointer->initialize(pointerLocation, m_pGfx);
	ShowCursor(false);
}


TargetPointer::~TargetPointer()
{
	if (m_pTargetPointer)
	{
		delete m_pTargetPointer;
		m_pTargetPointer = nullptr;
	}
	ShowCursor(true);
}


void TargetPointer::update(GameObject* gameobject)
{
	DirectX::XMVECTOR objectPosition = gameobject->getPosition();
	DirectX::XMFLOAT2 position;
	DirectX::XMStoreFloat2(&position, objectPosition);

	m_gameObjectPosition.x = position.x;
	m_gameObjectPosition.y = position.y;

	POINT mousePosition;
	GetCursorPos(&mousePosition);
	HWND gameWindow = FindWindow(L"MainApplicationWindow", L"Battle Tank");
	ScreenToClient(gameWindow, &mousePosition);

	m_mousePosition.x = mousePosition.x;
	m_mousePosition.y = mousePosition.y;

	D2D1::Matrix3x2F translationMatrix = D2D1::Matrix3x2F::Translation(D2D1::SizeF(m_mousePosition.x-m_pTargetPointer->getWidth()/2, m_mousePosition.y - m_pTargetPointer->getHeight()/2));
	m_pTargetPointer->setTransformation(translationMatrix);
}

void TargetPointer::render()
{	
	m_pTargetPointer->draw();
	m_pGfx->drawLine(m_gameObjectPosition, m_mousePosition);
}
