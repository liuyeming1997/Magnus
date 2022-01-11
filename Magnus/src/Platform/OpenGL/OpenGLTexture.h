#pragma once
#include <string>
#include "Magnus/Render/Texture.h"
namespace Magnus {
	class OpenGLTexture2D : public Texture2D
	{

	public:
		OpenGLTexture2D(const std::string& path);
		~OpenGLTexture2D();
		void Bind(unsigned int slot = 0) const override;

		inline unsigned int GetWidth() const override{ return m_Width; };
		inline unsigned int GetHeight() const override { return m_Height; };
	private:
		unsigned int m_RenderID;
		std::string m_FilePath;
		int m_Width, m_Height, m_BPP;
	};

}


