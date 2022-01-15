#pragma once
#include "VertexArray.h"
#include "RenderAPI.h"
#include "glm/glm.hpp"
namespace Magnus {
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RenderAPI->Init();
		}
		inline static void SetClearColor(const glm::vec4& color){
			s_RenderAPI->SetClearColor(color);
		}

		inline static void Clear(){
			s_RenderAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) {
			s_RenderAPI->DrawIndexed(vertexArray);
		}
		
		inline static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			s_RenderAPI->SetViewPort(x, y, width, height);
		}
	private:
		static RenderAPI* s_RenderAPI;
	};
}


