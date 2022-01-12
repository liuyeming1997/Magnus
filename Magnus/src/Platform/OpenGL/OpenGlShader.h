#pragma once
#include<string>
#include<unordered_map>
#include"glm/glm.hpp"
#include "Magnus/Render/Shader.h"
namespace Magnus {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& m_VertPath, const std::string& m_FragPath);
		~OpenGLShader();
		void Bind() const override;
		void UnBind() const override;
		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniform3f(const std::string& name, float v0, float v1, float v2);
		void SetUniform3f(const std::string& name, const glm::vec3& v);
		void SetUniforMat4f(const std::string& name, const glm::mat4& matrix);
	private:
		unsigned int m_RendererID;
		std::string m_VertPath;
		std::string m_FragPath;
		mutable std::unordered_map<std::string, int> m_uniformaLocationCache;

		int GetUniformLocation(const std::string& name) const;
		unsigned int CompileShader(const std::string& source, unsigned int type);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fagmentShader);
		ShaderProgramSource ParseShader(const std::string& VerPath, const std::string& FraPath);
	};

}
