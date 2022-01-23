#include "mgpch.h"
#include "Buffer.h"
#include "Magnus/Render/Render.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "RenderAPI.h"
namespace Magnus {
	Ref<VertexBuffer> VertexBuffer::Create(float* data, unsigned int size) {
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::NONE: 
			MG_CORE_ASSERT(false, "not use render API");
		case RenderAPI::API::OPENGL:
			return CreateRef<OpenGLVertexBuffer>(data, size);

		}
		MG_CORE_ASSERT(false, "find a new render api not defined");
		return nullptr;
	}

	Ref <IndexBuffer> IndexBuffer::Create(unsigned int* data, unsigned int size) {
		switch (RenderAPI::GetAPI())
		{ 
		case RenderAPI::API::NONE:
			MG_CORE_ASSERT(false, "not use render API");
		case RenderAPI::API::OPENGL:
			return CreateRef<OpenGLIndexBuffer>(data, size);

		}
		MG_CORE_ASSERT(false, "find a new render api not defined");
		return nullptr;
	}

}