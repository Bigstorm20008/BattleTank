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
	std::chrono::high_resolution_clock::time_point m_startGameTimePoint;
	std::chrono::high_resolution_clock::time_point m_currentGameTimePoint;
	std::chrono::high_resolution_clock::time_point m_previousTimePoint;
	std::chrono::high_resolution_clock::time_point m_currentTimePoint;
	m_currentTimePoint = m_previousTimePoint = m_startGameTimePoint = m_currentGameTimePoint = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds miliseconds40(20);
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
			m_currentTimePoint = std::chrono::high_resolution_clock::now();
			if (std::chrono::duration_cast<std::chrono::milliseconds>(m_currentTimePoint - m_previousTimePoint) >= miliseconds40)
			{
				m_pGame->update();
				m_pGame->render();
				m_previousTimePoint = m_currentTimePoint;
			}
		}
	}
	return static_cast<int>(msg.wParam);
}
