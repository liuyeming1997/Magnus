#include "mgpch.h"
#include "Buffer.h"
#include "Magnus/Render/Render.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
namespace Magnus {
	VertexBuffer* VertexBuffer::Create(float* data, unsigned int size) {
		switch (Render::Get())
		{
		case RenderAPI::NONE:
			MG_CORE_ASSERT(false, "not use render API");
		case RenderAPI::OPENGL:
			return new OpenGLVertexBuffer(data, size);

		}
		MG_CORE_ASSERT(false, "find a new render api not defined");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(unsigned int* data, unsigned int size) {
		switch (Render::Get())
		{
		case RenderAPI::NONE:
			MG_CORE_ASSERT(false, "not use render API");
		case RenderAPI::OPENGL:
			return new OpenGLIndexBuffer(data, size);

		}
		MG_CORE_ASSERT(false, "find a new render api not defined");
		return nullptr;
	}

}