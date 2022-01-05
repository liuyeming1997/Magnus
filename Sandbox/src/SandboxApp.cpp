#include <Magnus.h>
class ExampleLayer : public Magnus::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		MG_INFO("ExampleLayer::Update");
	}

	void OnEvent(Magnus::Event& event) override
	{
		MG_TRACE("{0}", event);
	}

};
class Sandbox : public Magnus::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Magnus::ImGuiLayer());
	}
	~Sandbox() {

	}

private: 

};
Magnus::Application* Magnus::CreateApplication() {
	return new Sandbox();
}

