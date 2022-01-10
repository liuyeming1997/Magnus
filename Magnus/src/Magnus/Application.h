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

		Camera m_Camera;

		void Run();
		void OnEvent(Event& event);
		void PushLayer(Layer * layer);
		void PushOverlay(Layer * layer);
		inline WindowBasic& GetWindow() { return *m_Window; }

		inline static Application& GetInstance() { return *s_Instance; }
	private:
		std::unique_ptr<WindowBasic> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		static Application* s_Instance;
		LayerStack m_LayerStack;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexArray> m_SquareVA;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Shader> Square_Shader;
	

		bool OnWindowClose(WindowCloseEvent& e);
		
		
	};
	//define in CLIENT 
	Application* CreateApplication();

}


