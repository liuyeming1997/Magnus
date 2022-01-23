#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//-----Entry Point------------------
#include "Magnus/Core/EntryPoint.h"
Sandbox2D::Sandbox2D() : Magnus::Layer("Render2D"), m_CameraControl(1280.0f / 720.0f) {

}
void Sandbox2D::OnAttach() {

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
	Magnus::Render2D::BeginScene(m_CameraControl.GetCamera());
	Magnus::Render2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Magnus::Render2D::EndScene();
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