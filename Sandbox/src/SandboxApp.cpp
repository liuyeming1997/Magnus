#include <Magnus.h>

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Sandbox2D.h"
class ExampleLayer : public Magnus::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraControl(1280.0f / 720.0f),
		m_SquarePosition(0.0f), m_ShaderLibrary()
	{

		m_VertexArray = Magnus::VertexArray::Create();
		m_VertexArray->Bind();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};


		Magnus::Ref<Magnus::VertexBuffer> m_VertexBuffer = Magnus::Ref<Magnus::VertexBuffer>
			(Magnus::VertexBuffer::Create(vertices, sizeof(vertices)));


		Magnus::BufferLayout layout = {
			{Magnus::ShaderDataType::Float3, "a_Position"},
			{Magnus::ShaderDataType::Float4, "a_Color"}
		};
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);


		unsigned int indices[3] = { 0, 1, 2 };
		Magnus::Ref<Magnus::IndexBuffer> m_IndexBuffer = Magnus::Ref<Magnus::IndexBuffer>(Magnus::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));

		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		auto& m_Shader = m_ShaderLibrary.Load("shader", "assert/shader/shader.vert",
			"assert/shader/shader.frag");

		m_SquareVA = Magnus::VertexArray::Create();
		m_SquareVA->Bind();
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Magnus::Ref<Magnus::VertexBuffer> squareVB;
		squareVB = Magnus::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Magnus::ShaderDataType::Float3, "a_Position" },
			{ Magnus::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Magnus::Ref<Magnus::IndexBuffer> squareIB;
		squareIB = Magnus::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

		auto Square_Shader = m_ShaderLibrary.Load("assert/shader/Texture.glsl");

		m_Texture = std::move(Magnus::Texture2D::Create("assert/texture/container2.png"));
		m_ChernoLogoTexture = std::move(Magnus::Texture2D::Create("assert/texture/ChernoLogo.png"));

		std::dynamic_pointer_cast<Magnus::OpenGLShader>(Square_Shader)->Bind();
		std::dynamic_pointer_cast<Magnus::OpenGLShader>(Square_Shader)->SetUniform1i("u_Texture", 0);
		
	}

	void OnUpdate(Magnus::Timestep ts) override
	{
		Magnus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Magnus::RenderCommand::Clear();

		

		m_CameraControl.OnUpdate(ts);
		/*if (Magnus::Input::IsKeyPressed(MG_KEY_I))
			m_SquarePosition.y += SquareMoveSpeed * ts;
		else if (Magnus::Input::IsKeyPressed(MG_KEY_K))
			m_SquarePosition.y -= SquareMoveSpeed * ts;
		else if (Magnus::Input::IsKeyPressed(MG_KEY_J))
			m_SquarePosition.x -= SquareMoveSpeed * ts;
		else if (Magnus::Input::IsKeyPressed(MG_KEY_L))
			m_SquarePosition.x += SquareMoveSpeed * ts;*/


		Magnus::Render::BeginScene(m_CameraControl.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		//std::dynamic_pointer_cast<Magnus::OpenGLShader>(Square_Shader)->Bind();
		//std::dynamic_pointer_cast<Magnus::OpenGLShader>(Square_Shader)->SetUniform3f("u_Color", m_SquareColor);
		//Magnus::Render::Submit(m_SquareVA, Square_Shader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		/*for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Magnus::Render::Submit(m_SquareVA, Square_Shader, transform);
			}
		}*/
		m_Texture->Bind();
		
		Magnus::Render::Submit(m_SquareVA, m_ShaderLibrary.GetShader("Texture"));
		m_ChernoLogoTexture->Bind();
		Magnus::Render::Submit(m_SquareVA, m_ShaderLibrary.GetShader("Texture"));
		//Magnus::Render::Submit(m_VertexArray, m_Shader);
		Magnus::Render::EndScene();
	}

	virtual void OnImGuiRender() override 
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Magnus::Event& event) override
	{
		if (Magnus::Input::IsKeyPressed(MG_KEY_SPACE)) {
			MG_INFO("checked press space");
		}
		m_CameraControl.OnEvent(event);
		
		//MG_TRACE("{0}", event);
	}


private:
	Magnus::Ref<Magnus::VertexArray> m_VertexArray;
	Magnus::Ref<Magnus::VertexArray> m_SquareVA;
	Magnus::Ref<Magnus::Texture2D> m_Texture;
	Magnus::Ref<Magnus::Texture2D>  m_ChernoLogoTexture;
	Magnus::ShaderLibrary m_ShaderLibrary;
	Magnus::CameraControl m_CameraControl;
	
	glm::vec3 m_SquarePosition;
	float SquareMoveSpeed = 2.0f;


	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
class Sandbox : public Magnus::Application
{
public:
	Sandbox() {
		
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
		
	}
	~Sandbox() {

	}

private: 

};
Magnus::Application* Magnus::CreateApplication() {
	return new Sandbox();
}

