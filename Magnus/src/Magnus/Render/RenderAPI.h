#pragma once
#include <glm/glm.hpp>
#include "VertexArray.h"
namespace Magnus {
	class RenderAPI
	{
	public:
		enum class API
		{
			NONE = 0, OPENGL = 1
		};
		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& backgroundColor) = 0;
		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}


