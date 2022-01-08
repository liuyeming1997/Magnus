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
		std::unique_ptr<WindowBasic> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		static Application* s_Instance;
		unsigned int m_VertexArray;
		LayerStack m_LayerStack;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

		bool OnWindowClose(WindowCloseEvent& e);
		
		
	};
	//define in CLIENT 
	Application* CreateApplication();

}


