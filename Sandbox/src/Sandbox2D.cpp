#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//-----Entry Point------------------
#include "Magnus/Core/EntryPoint.h"
Sandbox2D::Sandbox2D() : Magnus::Layer("Render2D"), m_CameraControl(1280.0f / 720.0f) {

}
void Sandbox2D::OnAttach() {

	m_SquareVA.reset(Magnus::VertexArray::Create());
	m_SquareVA->Bind();
	float squareVertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};

	
	Magnus::Ref<Magnus::VertexBuffer> squareVB;
	squareVB.reset(Magnus::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	
	squareVB->SetLayout({
		{ Magnus::ShaderDataType::Float3, "a_Position" },
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Magnus::Ref<Magnus::IndexBuffer> squareIB;
	squareIB.reset(Magnus::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);
	
	m_FlatColorShader = Magnus::Shader::Create("assert/shader/FlatColor.glsl");
	
	
}
void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Magnus::Timestep ts)
{
	// Update
	m_CameraControl.OnUpdate(ts);

	// Render
	Magnus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Magnus::RenderCommand::Clear();

	Magnus::Render::BeginScene(m_CameraControl.GetCamera());

	std::dynamic_pointer_cast<Magnus::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Magnus::OpenGLShader>(m_FlatColorShader)->SetUniform4f("u_Color", m_SquareColor);

	Magnus::Render::Submit(m_SquareVA, m_FlatColorShader,glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Magnus::Render::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Magnus::Event& e)
{
	m_CameraControl.OnEvent(e);
}