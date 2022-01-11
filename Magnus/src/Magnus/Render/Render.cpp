#include "mgpch.h"
#include "Render.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Magnus {
	Render::SceneData* Render::m_SceneData = new Render::SceneData;
	void Render::BeginScene(const Camera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetGetViewProjectionMatrix();
	}

	void Render::EndScene()
	{
	}

	void Render::Submit(const std::shared_ptr<VertexArray>& vertexArray, 
		const std::shared_ptr<Shader>& shader, 
		const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniforMat4f("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniforMat4f("u_Transform", transform);

		vertexArray->Bind();
	
 		RenderCommand::DrawIndexed(vertexArray);
	}
}