#include "mgpch.h"
#include "Application.h"
#include "Magnus/Render/Buffer.h"
#include <glad/glad.h>
 
namespace Magnus {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Magnus::ShaderDataType::Float:    return GL_FLOAT;
		case Magnus::ShaderDataType::Float2:   return GL_FLOAT;
		case Magnus::ShaderDataType::Float3:   return GL_FLOAT;
		case Magnus::ShaderDataType::Float4:   return GL_FLOAT;
		case Magnus::ShaderDataType::Mat3:     return GL_FLOAT;
		case Magnus::ShaderDataType::Mat4:     return GL_FLOAT;
		case Magnus::ShaderDataType::Int:      return GL_INT;
		case Magnus::ShaderDataType::Int2:     return GL_INT;
		case Magnus::ShaderDataType::Int3:     return GL_INT;
		case Magnus::ShaderDataType::Int4:     return GL_INT;
		case Magnus::ShaderDataType::Bool:     return GL_BOOL;
		}

		MG_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	Application::Application() {
		MG_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<WindowBasic>(WindowBasic::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
			

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
			

		{
			BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
			};
			m_VertexBuffer->SetLayout(layout);
		}
		const auto& layout = m_VertexBuffer->GetLayout();
		unsigned int index = 0;
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
				element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normalized? GL_TRUE : GL_FALSE, 
				layout.GetStride(),
				(const void *)element.Offset);
			index++;
		}
		
	
		unsigned int indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
	

		m_Shader = std::make_unique<Shader>("C:/dev/Magnus/Magnus/src/Magnus/Render/shader/shader.vert", 
			"C:/dev/Magnus/Magnus/src/Magnus/Render/shader/shader.frag");
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

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
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