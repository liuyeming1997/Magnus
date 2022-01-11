#include "mgpch.h"
#include "Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "Magnus/Render/Render.h"
#include "Platform/OpenGL/OpenGlShader.h"
namespace Magnus {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Render::GetAPI())
		{
			case RenderAPI::API::NONE:    MG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RenderAPI::API::OPENGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		MG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}