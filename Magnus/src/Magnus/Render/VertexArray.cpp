#include "mgpch.h"
#include "VertexArray.h"

#include "Render.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "RenderAPI.h"

namespace Magnus {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::NONE:    MG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OPENGL:  return CreateRef<OpenGLVertexArray>();
		}

		MG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}