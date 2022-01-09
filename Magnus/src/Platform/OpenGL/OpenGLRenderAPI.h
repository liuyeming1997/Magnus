#pragma once
#include "Magnus/Render/RenderAPI.h"
namespace Magnus {
	class OpenGLRenderAPI : public RenderAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& backgroundColor);
		virtual void Clear();

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);
	};
}


