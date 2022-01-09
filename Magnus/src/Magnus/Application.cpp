#include "mgpch.h"
#include "Application.h"
#include "Magnus/Render/Buffer.h"
#include <glad/glad.h>
 
namespace Magnus {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;
	Application::Application() {
		MG_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window.reset(WindowBasic::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->Bind();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
			

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
			

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
		};
		m_VertexBuffer->SetLayout(layout);
		
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		
	
		unsigned int indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_Shader = std::make_unique<Shader>("C:/dev/Magnus/Magnus/src/Magnus/Render/shader/shader.vert", 
			"C:/dev/Magnus/Magnus/src/Magnus/Render/shader/shader.frag");

		m_SquareVA.reset(VertexArray::Create());
		m_SquareVA->Bind();
		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		Square_Shader.reset(new Shader("C:/dev/Magnus/Magnus/src/Magnus/Render/shader/square.vert",
			"C:/dev/Magnus/Magnus/src/Magnus/Render/shader/square.frag"));
	}
	// app执行事件
	void  Application::OnEvent(Event& event) {
		EventDispatcher dispacher(event);
		//先分发事件
		dispacher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			//再判断哪个层执行事件（maybe)

			(*--it)->OnEvent(event);
			if (event.Handled)
				break;
		}
		//MG_CORE_TRACE("{0}", event);
	

	}
	Application::~Application() {

	}
	void Application::PushLayer(Layer * layer)
	{
		m_LayerStack.PushLayer(layer);
	
	}

	void Application::PushOverlay(Layer * layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
	void Application::Run() {
		while (m_Running) {
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT); 
			m_SquareVA->Bind();
			Square_Shader->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_VertexArray->Bind();
			m_Shader->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			//submit date
			for (Layer *& layer : m_LayerStack)
				layer->OnUpdate();
			
			//rendor
			m_ImGuiLayer->Begin();
			for (Layer *& layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
		

	}
	bool Application::OnWindowClose(WindowCloseEvent& e) 
	{
		m_Running = false;
		return true;

	}

}