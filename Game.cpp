#include "Game.h"


Game::Game()
{
	m_gfx = nullptr;
	m_pPlayerTank = nullptr;
	m_explosion = nullptr;
	m_background = nullptr;
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
		delete m_gfx;
		m_gfx = nullptr;
		return false;
	}

	initGameWorld();

	initInputComponents();
	initGraficsComponents();
	initPhysicsComponents();

	initGameObjects();

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
	if (m_background)
	{
		delete m_background;
		m_background = nullptr;
	}
	if (m_playerInput)
	{
		delete m_playerInput;
		m_playerInput = nullptr;
	}
	if (m_playerTankGrafics)
	{
		delete m_playerTankGrafics;
		m_playerTankGrafics = nullptr;
	}
	if (m_explosion)
	{
		delete m_explosion;
		m_explosion = nullptr;
	}
	if (m_targetPonter)
	{
		delete m_targetPonter;
		m_targetPonter = nullptr;
	}
}

void Game::initInputComponents()
{
	m_playerInput = new PlayerTankInputComponent;
}

void Game::initGraficsComponents()
{
	m_playerTankGrafics = new TankGraficsComponent(*m_gfx);
	wchar_t* tankBodyLocation = L"Resources\\BattleTank\\Tank1.PSD";
	wchar_t* tankTowerLocation = L"Resources\\BattleTank\\TankTower.PSD";
	m_playerTankGrafics->initComponent(*tankBodyLocation, *tankTowerLocation, 35);
	m_targetPonter = new TargetPointer(*m_gfx);
}

void Game::initPhysicsComponents()
{

}

void Game::initGameWorld()
{

}

void Game::initGameObjects()
{
	wchar_t* backgrondLocation = L"Resources\\Background\\background.PSD";
	m_background = new SpriteSheet;
	m_background->initialize(backgrondLocation, m_gfx);

	RECT rc;
	GetClientRect(m_gameWindow, &rc);
	m_pPlayerTank = new PlayerTank(m_playerTankGrafics, m_playerInput, m_targetPonter);
	m_pPlayerTank->setTankPosition((rc.right - rc.left) / 2, rc.bottom);

}


void Game::update()
{
	m_pPlayerTank->update();
}

void Game::render()
{
	m_gfx->beginDraw();
	m_gfx->clearScreen(1.f, 1.f, 1.f);
	m_background->draw();
	m_pPlayerTank->render();

	if (m_explosion)
	{
		m_explosion->animate();
		m_explosion->draw();
	}
	m_gfx->endDraw();
}

void Game::explosion()
{
	if (m_explosion)
	{
		delete m_explosion;
		m_explosion = nullptr;
	}
	wchar_t* explosionLocation = L"Resources\\Effects\\Explosion\\testExplosion.PSD";
	m_explosion = new SpriteSheet;
	m_explosion->initialize(explosionLocation, 100, m_gfx);

	POINT mousePosition;
	GetCursorPos(&mousePosition);
	HWND gameWindow = FindWindow(L"MainApplicationWindow", L"Battle Tank");
	ScreenToClient(gameWindow, &mousePosition);
	D2D1::Matrix3x2F& translateMatrix = D2D1::Matrix3x2F::Translation(D2D1::SizeF(static_cast<FLOAT>(mousePosition.x) - 100/2, static_cast<FLOAT>(mousePosition.y) - m_explosion->getHeight()/2));
	m_explosion->setTransformation(translateMatrix);
}

