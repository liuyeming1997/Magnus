#include "mgpch.h"
#include "Application.h"
#include "Magnus/Render/Buffer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Magnus/Render/Render.h"
#include "Magnus/Render/Render2D.h"
#include "Magnus/Render/RenderCommand.h"
#include "Magnus/Render/Camera.h"
#include "Magnus/Core/Timestep.h"
 
namespace Magnus {
	Application* Application::s_Instance = nullptr;
	Application::Application() {
		
		MG_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window.reset(WindowBasic::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		Render::Init();
		Render2D::Init();

		
	}
	// app执行事件
	void  Application::OnEvent(Event& event) {
		EventDispatcher dispacher(event);
		//先分发事件
		dispacher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispacher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
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
	void Application::PushLayer(Layer * layer)
	{
		m_LayerStack.PushLayer(layer);
	
	}

	void Application::PushOverlay(Layer * layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
	void Application::Run() {
		while (m_Running) {
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			//submit date
			if (!m_IsMini) {
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}
			//rendor
			m_ImGuiLayer->Begin();
			for (Layer * layer : m_LayerStack)
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
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetHeight() == 0 || e.GetWidth() == 0) {
			m_IsMini = true;
			return false;
		}
		m_IsMini = false;
		Render::OnWindowResize(e.GetWidth(), e.GetHeight());
		// 实验一下不往下传
		return false;

	}
}