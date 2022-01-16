#include "mgpch.h"
#include "CameraControl.h"
#include "Magnus/Core/KeyCode.h"
#include "Magnus/Core/Input.h"
#include "Magnus/Core/Core.h"
namespace Magnus {
	CameraControl::CameraControl(float _AspectRatio, bool _isRotate):m_AspectRatio(_AspectRatio), 
		m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, 
		-m_ZoomLevel, m_ZoomLevel), m_isRotate(_isRotate){

	}
	void CameraControl::OnUpdate(Timestep ts) {
		if (Input::IsKeyPressed(MG_KEY_W)) {
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) 
				* CameraMoveSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) 
				* CameraMoveSpeed * ts;
		}
		else if (Input::IsKeyPressed(MG_KEY_S)) {
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) 
				* CameraMoveSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation))
				* CameraMoveSpeed * ts;
		}
		else if (Input::IsKeyPressed(MG_KEY_A)) {
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) 
				* CameraMoveSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) 
				* CameraMoveSpeed * ts;
		}
		else if (Input::IsKeyPressed(MG_KEY_D)) {
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) 
				* CameraMoveSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) 
				* CameraMoveSpeed * ts;
		}
		if (m_isRotate) {
			if (Input::IsKeyPressed(MG_KEY_Q))
				m_CameraRotation += CameraRotateSpeed * ts;
			if (Input::IsKeyPressed(MG_KEY_E))
				m_CameraRotation -= CameraRotateSpeed * ts;
			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;
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
		MG_CORE_WARN("{0}  {1}",e.GetWidth(), e.GetHeight());
		m_Camera.SetOrthographic(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}