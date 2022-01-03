#pragma once
#include "Core.h"


namespace Magnus {
	class MAGNUS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		
	};
	//define in CLIENT 
	Application* CreateApplication();

}


