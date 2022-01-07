#pragma once
#include "Core.h"
#include "Window.h"
#include "Magnus/Events/KeyEvent.h"
#include "Magnus/Events/ApplicationEvent.h"
#include "Magnus/Events/MouseEvent.h"
#include "LayerStack.h"

#include "Magnus/ImGui/ImGuiLayer.h"

namespace Magnus {
	class MAGNUS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline WindowBasic& GetWindow() { return *m_Window; }

		inline static Application& GetInstance() { return *s_Instance; }
	private:
		std::unique_ptr<WindowBasic> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		static Application* s_Instance;

		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack m_LayerStack;
		
	};
	//define in CLIENT 
	Application* CreateApplication();

}


