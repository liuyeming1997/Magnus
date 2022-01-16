#pragma once
#include "Magnus/Core/Timestep.h"
#include "Magnus/Events/Event.h"
#include "Magnus/Events/ApplicationEvent.h"
#include "Magnus/Events/MouseEvent.h"
#include "Magnus/Render/Camera.h"
namespace Magnus {
	class CameraControl
	{
	public:
		CameraControl(float _AspectRatio, bool _isRotate = true);
		void OnUpdate(Timestep ts);
		void OnEvent(Event& event);

		inline Camera& GetCamera() {
			return m_Camera;
		}
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		Camera m_Camera;
		bool m_isRotate;
		glm::vec3 m_CameraPosition = { 0.0f,0.0f,0.0f };
		float CameraMoveSpeed = 1.0f;
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float CameraRotateSpeed = 2.1f;

		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	};
}


