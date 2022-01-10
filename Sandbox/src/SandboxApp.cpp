#include <Magnus.h>

#include "imgui/imgui.h"
class ExampleLayer : public Magnus::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Magnus::VertexArray::Create());
		m_VertexArray->Bind();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};


		std::shared_ptr<Magnus::VertexBuffer> m_VertexBuffer = std::shared_ptr<Magnus::VertexBuffer>
			(Magnus::VertexBuffer::Create(vertices, sizeof(vertices)));


		Magnus::BufferLayout layout = {
			{Magnus::ShaderDataType::Float3, "a_Position"},
			{Magnus::ShaderDataType::Float4, "a_Color"}
		};
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);


		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<Magnus::IndexBuffer> m_IndexBuffer = std::shared_ptr<Magnus::IndexBuffer>(Magnus::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));

		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_Shader = std::make_unique<Magnus::Shader>("C:/dev/Magnus/Magnus/src/Magnus/Render/shader/shader.vert",
			"C:/dev/Magnus/Magnus/src/Magnus/Render/shader/shader.frag");

		m_SquareVA.reset(Magnus::VertexArray::Create());
		m_SquareVA->Bind();
		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Magnus::VertexBuffer> squareVB;
		squareVB.reset(Magnus::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Magnus::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Magnus::IndexBuffer> squareIB;
		squareIB.reset(Magnus::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		Square_Shader.reset(new Magnus::Shader("C:/dev/Magnus/Magnus/src/Magnus/Render/shader/square.vert",
			"C:/dev/Magnus/Magnus/src/Magnus/Render/shader/square.frag"));
		
	}

	void OnUpdate(Magnus::Timestep ts) override
	{
		Magnus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Magnus::RenderCommand::Clear();

		MG_INFO(ts);
		if (Magnus::Input::IsKeyPressed(MG_KEY_UP)) 
			m_CameraPosition.y += CameraMoveSpeed * ts;
		else if (Magnus::Input::IsKeyPressed(MG_KEY_DOWN)) 
			m_CameraPosition.y -= CameraMoveSpeed * ts;
		else if (Magnus::Input::IsKeyPressed(MG_KEY_LEFT))
			m_CameraPosition.x -= CameraMoveSpeed * ts;
		else if (Magnus::Input::IsKeyPressed(MG_KEY_RIGHT))
			m_CameraPosition.x += CameraMoveSpeed * ts;

		if (Magnus::Input::IsKeyPressed(MG_KEY_A))
			m_CameraRotation += CameraRotateSpeed * ts;
		if (Magnus::Input::IsKeyPressed(MG_KEY_D))
			m_CameraRotation -= CameraRotateSpeed * ts;
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Magnus::Render::BeginScene(m_Camera);
		Magnus::Render::Submit(m_SquareVA, Square_Shader);
		Magnus::Render::Submit(m_VertexArray, m_Shader);
		Magnus::Render::EndScene();
	}

	virtual void OnImGuiRender() override 
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello world");
		ImGui::End();
	}

	void OnEvent(Magnus::Event& event) override
	{
		if (Magnus::Input::IsKeyPressed(MG_KEY_SPACE)) {
			MG_INFO("checked press space");
		}
		
		//MG_TRACE("{0}", event);
	}


private:
	std::shared_ptr<Magnus::VertexArray> m_VertexArray;
	std::shared_ptr<Magnus::VertexArray> m_SquareVA;
	std::shared_ptr<Magnus::Shader> m_Shader;
	std::shared_ptr<Magnus::Shader> Square_Shader;

	Magnus::Camera m_Camera;
	glm::vec3 m_CameraPosition;
	float CameraMoveSpeed = 1.0f;
	float m_CameraRotation = 0.0f;
	float CameraRotateSpeed = 2.1f;
};
class Sandbox : public Magnus::Application
{
public:
	Sandbox() {
		
		PushLayer(new ExampleLayer());
		
	}
	~Sandbox() {

	}

private: 

};
Magnus::Application* Magnus::CreateApplication() {
	return new Sandbox();
}

