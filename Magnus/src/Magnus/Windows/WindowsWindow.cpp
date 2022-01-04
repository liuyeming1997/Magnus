#include "mgpch.h"
#include "WindowsWindow.h"
namespace Magnus {
	static bool s_GLFWInitialized = false;

	WindowsWindow::WindowsWindow(const WindowAttribute& att) {
		Init(att);
	}
	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}
	WindowBasic* WindowBasic::Create(const WindowAttribute& att)
	{
		return new WindowsWindow(att);
	}
	void WindowsWindow::Init(const WindowAttribute& att) {
		m_Data.m_Title = att.m_Title;
		m_Data.m_Height = att.m_Height;
		m_Data.m_Width = att.m_Width;

		MG_CORE_INFO("Creating window {0} ({1}, {2})", m_Data.m_Title, m_Data.m_Width, m_Data.m_Height);

		if (!s_GLFWInitialized) {
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			MG_CORE_ASSERT(success, "Could not intialize GLFW!");
			s_GLFWInitialized = true;
		}
		m_Window = glfwCreateWindow((int)att.m_Width, (int)att.m_Height, att.m_Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

	}
	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.m_VSync = enabled;
	}
	bool WindowsWindow::IsVSync() const
	{
		return m_Data.m_VSync;
	}

}