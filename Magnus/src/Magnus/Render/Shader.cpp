#include "mgpch.h"
#include "Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "Magnus/Render/Render.h"
#include "Platform/OpenGL/OpenGlShader.h"
namespace Magnus {
	Ref<Shader> Shader::Create(const std::string& filepath) {
		switch (Render::GetAPI())
		{
		case RenderAPI::API::NONE:    MG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OPENGL:  return std::make_shared<OpenGLShader>(filepath);
		}
		MG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Render::GetAPI())
		{
			case RenderAPI::API::NONE:    MG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RenderAPI::API::OPENGL:  return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		MG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}