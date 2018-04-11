#include "Game.h"


Game::Game()
{
	m_gfx = nullptr;
	m_pPlayerTank = nullptr;
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

	intGameObjects();
	return true;
}


void Game::freeAllResources()
{
	if (m_gfx)
	{
		delete m_gfx;
		m_gfx = nullptr;
	}
	if (m_pPlayerTank)
	{
		delete m_pPlayerTank;
		m_pPlayerTank = nullptr;
	}
}


void Game::intGameObjects()
{
	PlayerTankInputComponent* playerInput = new PlayerTankInputComponent;
	TankGraficsComponent* tankGrafics = new TankGraficsComponent(*m_gfx);
	wchar_t* tankBodyLocation = L"D:\\MyGames\\BattleTank\\BattleTank\\Resources\\BattleTank\\Tank1.PSD";
	wchar_t* tankTowerLocation = L"D:\\MyGames\\BattleTank\\BattleTank\\Resources\\BattleTank\\TankTower.PSD";
	tankGrafics->initComponent(*tankBodyLocation, *tankTowerLocation,35);
	m_pPlayerTank = new PlayerTank(tankGrafics, playerInput);
}


void Game::update()
{

}
void Game::render()
{
	m_gfx->beginDraw();
	m_gfx->clearScreen(1.f, 1.f, 1.f);

	m_pPlayerTank->update();

	m_gfx->endDraw();
}

