#pragma once

#include "Magnus/Layer.h"
#include "Magnus/Events/MouseEvent.h"	
#include "Magnus/Events/KeyEvent.h"
#include "Magnus/Events/ApplicationEvent.h"

namespace Magnus {

	class MAGNUS_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressEvent& e);
		bool OnKeyReleasedEvent(KeyReleaseEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		float m_Time = 0.0f;
	};

}