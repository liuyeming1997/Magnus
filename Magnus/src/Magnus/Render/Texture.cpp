#include "mgpch.h"
#include "Texture.h"
#include "Render.h"
#include "Platform/OpenGL/OpenGLTexture.h"
namespace Magnus {
	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Render::GetAPI())
		{
		case RenderAPI::API::NONE:    MG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OPENGL:  return std::make_shared<OpenGLTexture2D>(path);
		}

		MG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}