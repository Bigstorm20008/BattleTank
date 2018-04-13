#include "Application.h"


Application::Application()
{
	m_mainView = new MainApplicationWindow(L"MainApplicationWindow", L"Battle Tank");
	m_pGame = new Game;
	m_pGame->initalize(m_mainView->getHandle());
}


Application::~Application()
{
	
	if (m_mainView)
	{
		delete m_mainView;
		m_mainView = nullptr;
	}
	if (m_pGame)
	{
		delete m_pGame;
		m_pGame = nullptr;
	}
}

int Application::run()
{
	MSG msg; 
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT)
	{   
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				m_pGame->explosion();
			}
			DispatchMessage(&msg);
			TranslateMessage(&msg);
		}
		else
		{
			m_pGame->update();
			m_pGame->render();
		}
	}
	return static_cast<int>(msg.wParam);
}
