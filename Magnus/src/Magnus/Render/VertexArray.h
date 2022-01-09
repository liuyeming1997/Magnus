#pragma once
#include "Magnus/Render/Buffer.h"
#include <memory>
#include <vector>
namespace Magnus {
	class VertexArray
	{
	public:
		virtual ~VertexArray() {};

		virtual void Bind()const = 0;
		virtual void UnBind()const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;


		static VertexArray* Create();
	};
}