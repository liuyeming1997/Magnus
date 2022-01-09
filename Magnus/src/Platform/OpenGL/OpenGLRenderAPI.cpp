#include "mgpch.h"
#include "OpenGLRenderAPI.h"
#include <glad/glad.h>
namespace Magnus {
	void OpenGLRenderAPI::SetClearColor(const glm::vec4& backgroundColor) {
		glClearColor(0.1f, 0.1f, 0.1f, 1);
	}
	void OpenGLRenderAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}