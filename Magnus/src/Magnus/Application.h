#pragma once
#include "Core.h"
#include<cstdio>

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


