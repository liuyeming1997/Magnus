#include "mgpch.h"
#include "Render.h"
#include "RenderCommand.h"
namespace Magnus {
	void Render::BeginScene()
	{
	}

	void Render::EndScene()
	{
	}

	void Render::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}