#pragma once
#include "Magnus/Render/Buffer.h"
namespace Magnus {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		
		OpenGLVertexBuffer(float* data, unsigned int size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void UnBind() const override;
		const BufferLayout& GetLayout() const override { return m_Layout; };
		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
	private:
		unsigned int m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	public:
		OpenGLIndexBuffer(const unsigned int* data, unsigned int count);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void UnBind() const override;
		inline unsigned int GetCount() const override {
			return m_Count;
		};
	};
}


