#include "Game.h"


Game::Game()
{
	m_gfx = nullptr;
	m_soundEngine = nullptr;
	m_pPlayerTank = nullptr;
	m_explosion = nullptr;
	m_background = nullptr;
	m_explosionSound = nullptr;
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

	m_soundEngine = new SoundEngine;
	m_soundEngine->initialize();

	initSoundsComponents();
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
	if (m_backgroundMusic)
	{
		m_backgroundMusic->stop();
		delete m_backgroundMusic;
		m_backgroundMusic = nullptr;
	}
	if (m_startEngine)
	{
		m_startEngine->stop();
		delete m_startEngine;
		m_startEngine = nullptr;
	}
	if (m_soundEngine)
	{
		delete m_soundEngine;
		m_soundEngine = nullptr;
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
	m_playerTankGrafics->initComponent(*tankBodyLocation, *tankTowerLocation);
	m_targetPonter = new TargetPointer(*m_gfx);
	m_tankTrack = new TankTrackGC(*m_gfx);
	m_smoke = new TankSmoke(*m_gfx);
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
	m_pPlayerTank = new PlayerTank(m_playerTankGrafics, m_playerInput, m_targetPonter, m_tankTrack, m_smoke, m_soundEngine);
	m_pPlayerTank->setTankPosition((rc.right - rc.left) / 2, rc.bottom);
}


void Game::update()
{
	if (m_backgroundMusic)
	{
		if (!m_backgroundMusic->isPlaying())
		{
			m_backgroundMusic->restart();
			m_backgroundMusic->play();
		}
	}
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
	m_shootSound->stop();
	m_shootSound->restart();
	m_shootSound->play();
	wchar_t* explosionLocation = L"Resources\\Effects\\Explosion\\testExplosion.PSD";
	m_explosion = new SpriteSheet;
	m_explosion->initialize(explosionLocation, 100, m_gfx);

	POINT mousePosition;
	GetCursorPos(&mousePosition);
	HWND gameWindow = FindWindow(L"MainApplicationWindow", L"Battle Tank");
	ScreenToClient(gameWindow, &mousePosition);
	D2D1::Matrix3x2F& translateMatrix = D2D1::Matrix3x2F::Translation(D2D1::SizeF(static_cast<FLOAT>(mousePosition.x) - 100/2, static_cast<FLOAT>(mousePosition.y) - m_explosion->getHeight()/2));
	m_explosion->setTransformation(translateMatrix);
	m_explosionSound->stop();
	m_explosionSound->restart();
	m_explosionSound->play();
}


void Game::initSoundsComponents()
{
	SoundFactory soundFactory(*m_soundEngine);
	m_backgroundMusic = soundFactory.createSoundFromFile("Resources\\sounds\\cephei_mc_cataclysm.wav");
	m_backgroundMusic->setVolume(0.1f);
	m_backgroundMusic->play();

	m_startEngine = soundFactory.createSoundFromFile("Resources\\sounds\\startEngine.wav");
	m_startEngine->setVolume(0.1f);
	m_startEngine->play();

	m_explosionSound = soundFactory.createSoundFromFile("Resources\\sounds\\explosion1.wav");
	m_explosionSound->setVolume(1.0f);

	m_shootSound = soundFactory.createSoundFromFile("Resources\\sounds\\shoot.wav");
	m_shootSound->setVolume(1.f);
}

