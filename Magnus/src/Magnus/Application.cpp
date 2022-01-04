#include "mgpch.h"
#include "Application.h"
#include <GLFW/glfw3.h>

namespace Magnus {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application::Application() {
		m_Window = std::unique_ptr<WindowBasic>(WindowBasic::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));
	}
	void  Application::OnEvent(Event& event) {
		EventDispatcher dispacher(event);
		dispacher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		MG_CORE_TRACE("{0}", event);
		//MG_CORE_TRACE("{0}", event);

	}
	Application::~Application() {

	}
	void Application::Run() {
		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
		

	}
	bool Application::OnWindowClose(WindowCloseEvent& e) 
	{
		m_Running = false;
		return true;

	}

}