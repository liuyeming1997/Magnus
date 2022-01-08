#include <Magnus.h>

#include "imgui/imgui.h"
class ExampleLayer : public Magnus::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		
	}

	void OnUpdate() override
	{
		//MG_INFO("ExampleLayer::Update");
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

