#pragma once
#include "RenderAPI.h"
#include "Magnus/Render/Camera.h"
#include "Magnus/Render/Shader.h"
namespace Magnus {
	class  Render
	{
	public:

		static void Init();
		static void BeginScene(const Camera& camra);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, 
			const Ref<Shader>& shader,
			const glm::mat4& transform = glm::mat4(1.0f));

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;

	};


}