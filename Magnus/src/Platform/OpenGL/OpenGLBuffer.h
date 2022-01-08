#pragma once
#include "Magnus/Render/Buffer.h"
namespace Magnus {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer() {
			m_RendererID = 0;
		};
		OpenGLVertexBuffer(float* data, unsigned int size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void UnBind() const override;
	private:
		unsigned int m_RendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	public:
		OpenGLIndexBuffer() {
			m_RendererID = 0;
			m_Count = 0;
		};
		OpenGLIndexBuffer(const unsigned int* data, unsigned int count);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void UnBind() const override;
		inline unsigned int GetCount() const {
			return m_Count;
		};
	};
}


