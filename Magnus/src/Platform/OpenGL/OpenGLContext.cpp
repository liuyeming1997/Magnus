#include "mgpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
namespace Magnus {
	OpenGLContext::OpenGLContext(GLFWwindow* _WindowHandle)
		:m_WindowHandle(_WindowHandle){
		MG_CORE_ASSERT(_WindowHandle, "Window handle is null!")
	}
	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MG_CORE_ASSERT(status, "Failed to initialize Glad!");
		MG_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		MG_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		MG_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffer() {
		glfwSwapBuffers(m_WindowHandle);

	}
}