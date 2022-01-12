#pragma once
#include "Magnus/Render/RenderAPI.h"
namespace Magnus {
	class OpenGLRenderAPI : public RenderAPI
	{
	public:
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& backgroundColor) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}


