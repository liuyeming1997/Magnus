#include "mgpch.h"
#include "Application.h"
#include <glad/glad.h>
 
namespace Magnus {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;
	Application::Application() {
		MG_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<WindowBasic>(WindowBasic::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer =new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}
	// app执行事件
	void  Application::OnEvent(Event& event) {
		EventDispatcher dispacher(event);
		//先分发事件
		dispacher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			//再判断哪个层执行事件（maybe)

			(*--it)->OnEvent(event);
			if (event.Handled)
				break;
		}
		//MG_CORE_TRACE("{0}", event);
	

	}
	Application::~Application() {

	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
	void Application::Run() {
		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT); 
			//submit date
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			
			//rendor
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
		

	}
	bool Application::OnWindowClose(WindowCloseEvent& e) 
	{
		m_Running = false;
		return true;

	}

}