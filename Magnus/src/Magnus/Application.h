#pragma once
#include "Core.h"
#include "Window.h"
#include "Magnus/Events/KeyEvent.h"
#include "Magnus/Events/ApplicationEvent.h"
#include "Magnus/Events/MouseEvent.h"

namespace Magnus {
	class MAGNUS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);
	private:
		std::unique_ptr<WindowBasic> m_Window;
		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent& e);
		
	};
	//define in CLIENT 
	Application* CreateApplication();

}


