#include "mgpch.h"
#include "Application.h"
#include "Magnus/Events/KeyEvent.h"
#include "Magnus/Events/ApplicationEvent.h"
#include <GLFW/glfw3.h>

namespace Magnus {
	Application::Application() {
		m_Window = std::unique_ptr<WindowBasic>(WindowBasic::Create());
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
}