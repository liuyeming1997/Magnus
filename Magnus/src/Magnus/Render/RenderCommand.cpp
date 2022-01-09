#include "mgpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"
namespace Magnus {
	  RenderAPI* RenderCommand::s_RenderAPI = new OpenGLRenderAPI();
}