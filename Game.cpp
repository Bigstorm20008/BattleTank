#include "Game.h"


Game::Game()
{
	
}


Game::~Game()
{
	freeAllResources();
}

bool Game::initalize(HWND gameWindow)
{
	if (!gameWindow)
	{
		MessageBox(NULL, L"�� ������� ���� ��� ����", L"������ ������������� ����� Game", MB_OK);
		return false;
	}

	m_gameWindow = gameWindow;

	m_gfx = new Grafics2D;
	if (!m_gfx->init(m_gameWindow))
	{
		MessageBox(NULL, L"�� ������� ���������������� ����������� ����������", L"������ ������������� ����� Game", MB_OK);
		freeAllResources();
		return false;
	}

	return true;
}


void Game::freeAllResources()
{
	if (m_gfx)
	{
		delete m_gfx;
		m_gfx = nullptr;
	}
}
