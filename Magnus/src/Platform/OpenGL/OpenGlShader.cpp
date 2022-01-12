#include "mgpch.h"
#include "Magnus/Log.h"
#include "OpenGlShader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
namespace Magnus {
    OpenGLShader::OpenGLShader(const std::string& _Vertpath, const std::string& _Fragpath) :m_VertPath(_Vertpath), m_FragPath(_Fragpath), m_RendererID(0) {
        ShaderProgramSource pt = ParseShader(_Vertpath, _Fragpath);
        m_RendererID = CreateShader(pt.vertexSource, pt.FragmentSource);
    }
    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind() const {
        glUseProgram(m_RendererID);
    }
    void OpenGLShader::UnBind() const {
        glUseProgram(0);
    }
    void OpenGLShader::SetUniform1i(const std::string& name, int value) {
        glUniform1i(GetUniformLocation(name), value);

    }
    void OpenGLShader::SetUniform1f(const std::string& name, float value) {
        glUniform1f(GetUniformLocation(name), value);

    }
    void OpenGLShader::SetUniforMat4f(const std::string& name, const glm::mat4& matrix) {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }
    void OpenGLShader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
        glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
    }
    void OpenGLShader::SetUniform3f(const std::string& name, float v0, float v1, float v2) {
        glUniform3f(GetUniformLocation(name), v0, v1, v2);
    }
    void OpenGLShader::SetUniform3f(const std::string& name, const glm::vec3& v) {
        glUniform3f(GetUniformLocation(name), v.x, v.y, v.z);
    }
    int OpenGLShader::GetUniformLocation(const std::string& name) const {
        if (m_uniformaLocationCache.find(name) != m_uniformaLocationCache.end()) {
            return m_uniformaLocationCache[name];
        }
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        if (location == -1)
            MG_CORE_WARN("warning: uniform {0} doesm't exist!", name);
        m_uniformaLocationCache[name] = location;

        return location;
    }
    ShaderProgramSource OpenGLShader::ParseShader(const std::string& VerPath, const std::string& FraPath) {
        std::ifstream streamVert(VerPath);
        std::stringstream ss[2];
        std::string lineVert;
        while (getline(streamVert, lineVert)) {
            ss[0] << lineVert << "\n";
        }

        std::ifstream streamFrag(FraPath);
        std::string lineFrag;
        while (getline(streamFrag, lineFrag)) {
            ss[1] << lineFrag << "\n";
        }


        return { ss[0].str(), ss[1].str() };
    }
    unsigned int OpenGLShader::CompileShader(const std::string& source, unsigned int type) {

        // Create an empty shader handle
        unsigned int id = glCreateShader(type);
        // Send the vertex source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        // Compile the shader
        glCompileShader(id);
        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            // The maxLength includes the NULL character
            std::vector<char> infoLog(length);
            glGetShaderInfoLog(id, length, &length, &infoLog[0]);
            glDeleteShader(id);
            if (type == GL_VERTEX_SHADER) {
                MG_CORE_ERROR("this is vertex shader ");
            }
            else if (type == GL_FRAGMENT_SHADER) {
                MG_CORE_ERROR("this is fragment shader ");
            }
            MG_CORE_ERROR("{0}", infoLog.data());
            MG_CORE_ASSERT(false, "shader {0} compilation failure!");
            return 0;
        }


        return id;

    }
    unsigned int OpenGLShader::CreateShader(const std::string& vertexShader, const std::string& fagmentShader) {
        if (vertexShader.size() == 0) {
            MG_CORE_ASSERT(false, "input vertex shader error");
        }
        if (fagmentShader.size() == 0) {
            MG_CORE_ASSERT(false, "input fragment shader error");
        }

        unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
        unsigned int fs = CompileShader(fagmentShader, GL_FRAGMENT_SHADER);
        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        unsigned int program = glCreateProgram();
        // Attach our shaders to our program
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        int isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            int maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<char> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);
            // Don't leak shaders either.
            glDeleteShader(vs);
            glDeleteShader(fs);

            MG_CORE_ERROR("{0}", infoLog.data());
            MG_CORE_ASSERT(false, "Shader link failure!");
            return 0;
        }

        glDetachShader(program, vs);
        glDetachShader(program, fs);

        return program;

    }
}