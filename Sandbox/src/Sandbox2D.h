#pragma once
#include <Magnus.h>

class Sandbox2D : public Magnus::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Magnus::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Magnus::Event & e) override;
private:
	Magnus::Ref<Magnus::VertexArray> m_SquareVA;
	Magnus::Ref<Magnus::Shader> m_FlatColorShader;
	Magnus::CameraControl m_CameraControl;
	float SquareMoveSpeed = 2.0f;


	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};