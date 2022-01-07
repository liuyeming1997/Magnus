#include "mgpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Magnus/Application.h"

namespace Magnus {
#define BIND_IMGUIEVENT_FN(x) std::bind(&ImGuiLayer::x, this, std::placeholders::_1)
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMPORARY: should eventually use Magnus key codes
		io.KeyMap[ImGuiKey_Tab] = MG_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = MG_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = MG_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = MG_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = MG_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = MG_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = MG_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = MG_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = MG_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = MG_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = MG_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = MG_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = MG_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = MG_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = MG_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = MG_KEY_A;
		io.KeyMap[ImGuiKey_C] = MG_KEY_C;
		io.KeyMap[ImGuiKey_V] = MG_KEY_V;
		io.KeyMap[ImGuiKey_X] = MG_KEY_X;
		io.KeyMap[ImGuiKey_Y] = MG_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = MG_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::GetInstance();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;
		//MG_INFO("time is: {0}", m_Time);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcherEvent(event);
		dispatcherEvent.Dispatch<MouseButtonPressedEvent>(BIND_IMGUIEVENT_FN(OnMouseButtonPressedEvent));
		dispatcherEvent.Dispatch<MouseButtonReleasedEvent>(BIND_IMGUIEVENT_FN(OnMouseButtonReleasedEvent));
		dispatcherEvent.Dispatch<MouseMovedEvent>(BIND_IMGUIEVENT_FN(OnMouseMovedEvent));
		dispatcherEvent.Dispatch<MouseScrolledEvent>(BIND_IMGUIEVENT_FN(OnMouseScrolledEvent));
		dispatcherEvent.Dispatch<KeyPressEvent>(BIND_IMGUIEVENT_FN(OnKeyPressedEvent));
		dispatcherEvent.Dispatch<KeyReleaseEvent>(BIND_IMGUIEVENT_FN(OnKeyReleasedEvent));
		dispatcherEvent.Dispatch<KeyTypedEvent>(BIND_IMGUIEVENT_FN(OnKeyTypedEvent));
		dispatcherEvent.Dispatch<WindowResizeEvent>(BIND_IMGUIEVENT_FN(OnWindowResizeEvent));
	

	}
	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}
	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;

	}
	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}
	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += e.GetXOffset();
		io.MouseWheelH += e.GetYOffset();

		return false;
	}
	bool ImGuiLayer::OnKeyPressedEvent(KeyPressEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;
		io.KeyCtrl = io.KeysDown[MG_KEY_LEFT_CONTROL] || io.KeysDown[MG_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[MG_KEY_LEFT_SHIFT] || io.KeysDown[MG_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[MG_KEY_LEFT_ALT] || io.KeysDown[MG_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[MG_KEY_LEFT_SUPER] || io.KeysDown[MG_KEY_RIGHT_SUPER];
		return false;
	}
	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleaseEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;
		
		return false;
	}
	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);

		return false;
		
	}
	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}

}