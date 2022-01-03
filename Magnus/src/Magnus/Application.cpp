#include "Application.h"
#include "Magnus/Events/KeyEvent.h"
#include "Magnus/Events/ApplicationEvent.h"
#include "Log.h"
namespace Magnus {
	Application::Application() {

	}
	Application::~Application() {

	}
	void Application::Run() {
		unsigned int x = 1280;
		unsigned int y = 720;
		WindowResizeEvent e(x, y);
		if (e.IsInCategory(EventCategoryApplication))
		{
			MG_CLIENT_TRACE(e.ToString());
			std::cout << e << std::endl;
		}
		/*
		if (e.IsInCategory(EventCategoryInput))
		{
			MG_CLIENT_TRACE(e);
		}
		while (1);*/
		

	}
}