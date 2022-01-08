#pragma once
#include "Magnus/Render/GraphicContext.h"
#include <GLFW/glfw3.h>
namespace Magnus {

	class OpenGLContext : public GraphicContext
	{
	public:
		OpenGLContext(GLFWwindow* _WindowHandle);

		void Init() override;
		void SwapBuffer() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}

