#include "mgpch.h"
#include "CameraControl.h"
#include "Magnus/KeyCode.h"
#include "Magnus/Input.h"
#include "Magnus/Core.h"
namespace Magnus {
	CameraControl::CameraControl(float _AspectRatio, bool _isRotate):m_AspectRatio(_AspectRatio), 
		m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, 
		-m_ZoomLevel, m_ZoomLevel), m_isRotate(_isRotate){

	}
	void CameraControl::OnUpdate(Timestep ts) {
		if (Input::IsKeyPressed(MG_KEY_W))
			m_CameraPosition.y += CameraMoveSpeed * ts;
		else if (Input::IsKeyPressed(MG_KEY_S))
			m_CameraPosition.y -= CameraMoveSpeed * ts;
		else if (Input::IsKeyPressed(MG_KEY_A))
			m_CameraPosition.x -= CameraMoveSpeed * ts;
		else if (Input::IsKeyPressed(MG_KEY_D))
			m_CameraPosition.x += CameraMoveSpeed * ts;
		if (m_isRotate) {
			if (Input::IsKeyPressed(MG_KEY_Q))
				m_CameraRotation += CameraRotateSpeed * ts;
			if (Input::IsKeyPressed(MG_KEY_E))
				m_CameraRotation -= CameraRotateSpeed * ts;
			m_Camera.SetRotation(m_CameraRotation);
		}
		m_Camera.SetPosition(m_CameraPosition);
	
	}
	void CameraControl::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(CameraControl::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(CameraControl::OnWindowResized));
	}
	bool CameraControl::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetOrthographic(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool CameraControl::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetOrthographic(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}