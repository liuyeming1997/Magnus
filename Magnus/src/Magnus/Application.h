#pragma once
#include "Core.h"
#include "Window.h"

namespace Magnus {
	class MAGNUS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<WindowBasic> m_Window;
		bool m_Running = true;
		
	};
	//define in CLIENT 
	Application* CreateApplication();

}


