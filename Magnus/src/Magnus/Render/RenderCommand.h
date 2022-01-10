#pragma once
#include "VertexArray.h"
#include "RenderAPI.h"
#include "glm/glm.hpp"
namespace Magnus {
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color){
			s_RenderAPI->SetClearColor(color);
		}

		inline static void Clear(){
			s_RenderAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
			s_RenderAPI->DrawIndexed(vertexArray);
		}
	private:
		static RenderAPI* s_RenderAPI;
	};
}

