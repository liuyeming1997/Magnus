#include "mgpch.h"
#include "Render.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Magnus {
	Scope<Render::SceneData> Render::s_SceneData = CreateScope<Render::SceneData>();
	void Render::Init() {
		RenderCommand::Init();
	}
	void Render::BeginScene(const Camera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetGetViewProjectionMatrix();
	}

	void Render::EndScene()
	{
	}

	void Render::Submit(const Ref<VertexArray>& vertexArray, 
		const Ref<Shader>& shader, 
		const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniforMat4f("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniforMat4f("u_Transform", transform);

		vertexArray->Bind();
	
 		RenderCommand::DrawIndexed(vertexArray);
	}
	void Render::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewPort(0, 0, width, height);
	}
}