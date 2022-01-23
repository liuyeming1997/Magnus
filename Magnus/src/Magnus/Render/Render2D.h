#pragma once
#include "Magnus/Render/Camera.h"
#include "Magnus/Render/Camera.h"
namespace Magnus {
	class Render2D
	{
	public:
		static void Init();
		static void BeginScene(const Camera& camera);
		static void EndScene();
		static void ShutDown();
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

	};

}


