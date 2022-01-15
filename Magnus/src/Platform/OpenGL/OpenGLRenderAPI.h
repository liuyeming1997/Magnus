#pragma once
#include "Magnus/Render/RenderAPI.h"
namespace Magnus {
	class OpenGLRenderAPI : public RenderAPI
	{
	public:
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& backgroundColor) override;
		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}


