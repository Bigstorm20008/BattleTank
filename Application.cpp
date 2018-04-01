#include "Application.h"


Application::Application()
{
	m_mainView = new MainApplicationWindow(L"MainApplicationWindow", L"Battle Tank");
}


Application::~Application()
{
	
	if (m_mainView)
	{
		delete m_mainView;
		m_mainView = nullptr;
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
			DispatchMessage(&msg);
			TranslateMessage(&msg);
		}
		else
		{
		
		}
	}
	return static_cast<int>(msg.wParam);
}
