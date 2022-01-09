#include "mgpch.h"
#include "VertexArray.h"

#include "Render.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Magnus {

	VertexArray* VertexArray::Create()
	{
		switch (Render::Get())
		{
		case RenderAPI::NONE:    MG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::OPENGL:  return new OpenGLVertexArray();
		}

		MG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}