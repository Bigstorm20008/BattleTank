#include "Game.h"


Game::Game()
{
	m_playerTank = nullptr;
}


Game::~Game()
{
	freeAllResources();
}

bool Game::initalize(HWND gameWindow)
{
	if (!gameWindow)
	{
		MessageBox(NULL, L"Не указано окно для игры", L"Ошибка инициализации класс Game", MB_OK);
		return false;
	}

	m_gameWindow = gameWindow;

	m_gfx = new Grafics2D;
	if (!m_gfx->init(m_gameWindow))
	{
		MessageBox(NULL, L"Не удалось инициализировать графический ускоритель", L"Ошибка инициализации класс Game", MB_OK);
		
		return false;
	}

	m_playerTank = new SpriteSheet;
	if (!m_playerTank->initialize(L"Resources\\BattleTank\\Tank.PSD", 35, m_gfx))
	{
		MessageBox(NULL, L"Не удалось инициализировать танк игрока", L"Ошибка инициализации класс Game", MB_OK);
		freeAllResources();
		return false;
	}
	m_playerTank->moveTo(500, 200);
	m_playerTank->rotate(30, D2D1::Point2F(m_playerTank->getWidth() / 2, m_playerTank->getHeight() / 2));
	m_playerTank->draw();

	return true;
}


void Game::freeAllResources()
{
	if (m_gfx)
	{
		delete m_gfx;
		m_gfx = nullptr;
	}
	if (m_playerTank)
	{
		delete m_playerTank;
		m_playerTank = nullptr;
	}
}


LRESULT Game::messageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
