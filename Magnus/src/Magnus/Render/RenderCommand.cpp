#include "mgpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"
namespace Magnus {
	  Scope<RenderAPI> RenderCommand::s_RenderAPI = CreateScope<OpenGLRenderAPI>();
}