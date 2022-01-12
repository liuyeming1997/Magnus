#include "mgpch.h"
#include "OpenGLTexture.h"
#include "stb_image.h"
#include "glad/glad.h"
namespace Magnus {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_FilePath(path),m_Width(0), 
		m_Height(0), m_BPP(0) {
		stbi_set_flip_vertically_on_load(1);
		int width, height, channels;
		unsigned char* m_locationBuffer = stbi_load(path.c_str(), &width, &height, &channels, 4);
		MG_CORE_ASSERT(m_locationBuffer, "cant find img_path")
		m_Width = width;
		m_Height = height;
		m_BPP = channels;
		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		MG_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!")
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RenderID);
		glTextureStorage2D(m_RenderID, 1, internalFormat, m_Width, m_Height);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTextureParameteri(m_RenderID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(m_RenderID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RenderID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, m_locationBuffer);

		stbi_image_free(m_locationBuffer);

	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RenderID);
	}

	void OpenGLTexture2D::Bind(unsigned int slot) const
	{
		glBindTextureUnit(slot, m_RenderID);
	}
}