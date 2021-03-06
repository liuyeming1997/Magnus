#include "mgpch.h"
#include "Camera.h"
namespace Magnus{
	Camera::Camera(float left, float right, float bottom, float top):
		m_OrthographicMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f) {
		m_ViewProjectionMatrix = m_OrthographicMatrix * m_ViewMatrix;
		m_Position = { 0.0f, 0.0f ,0.0f };
	}
	void Camera::RecalculateViewMatrix() {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) 
			* glm::rotate(glm::mat4(1.0F), m_Rotation, glm::vec3(0,0,1));
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_OrthographicMatrix * m_ViewMatrix;
	}
}