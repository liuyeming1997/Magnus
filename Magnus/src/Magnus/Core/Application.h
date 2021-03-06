#pragma once
#include "Core.h"
#include "Window.h"
#include "Magnus/Events/KeyEvent.h"
#include "Magnus/Events/ApplicationEvent.h"
#include "Magnus/Events/MouseEvent.h"
#include "LayerStack.h"

#include "Magnus/ImGui/ImGuiLayer.h"
#include "Magnus/Render/Shader.h"
#include "Magnus/Render/Buffer.h"
#include "Magnus/Render/VertexArray.h"
#include "Magnus/Render/Camera.h"
namespace Magnus {

	class MAGNUS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);
		void PushLayer(Layer * layer);
		void PushOverlay(Layer * layer);
		inline WindowBasic& GetWindow() { return *m_Window; }

		inline static Application& GetInstance() { return *s_Instance; }
	private:
		Scope<WindowBasic> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_IsMini = false;
		static Application* s_Instance;
		LayerStack m_LayerStack;
	
		float m_LastFrameTime = 0.0f;
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		
		
	};
	//define in CLIENT 
	Application* CreateApplication();

}


