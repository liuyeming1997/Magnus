#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Magnus {
	class Camera
	{
	public:

		Camera::Camera(float left, float right, float bottom, float top);
		/*glm::mat4 SetViewMatrix()
		{
			return glm::lookAt(m_Position, m_Position + m_LookDir, m_LookUp);
		}*/
		void SetOrthographic(float left, float right, float bottom, float top) {
			m_OrthographicMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		}
		const glm::vec3& GetPosition() { return m_Position; }
		void inline SetPosition(glm::vec3 _Position) { m_Position = _Position; RecalculateViewMatrix();}

		float GetRotation() { return m_Rotation; }
		void inline SetRotation(float _Rotation) { m_Rotation = _Rotation; RecalculateViewMatrix(); }

		glm::mat4 GetGetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

 
		void inline SetLookDir(glm::vec3 _LookDir) { m_LookDir = _LookDir; }
		void inline SetLookUp (glm::vec3 _LookUp) { m_LookUp = _LookUp; }
		void inline SetScreenRato(float _ScreenRato) { m_ScreenRato = _ScreenRato; }
		void inline SetFov(float _Fov) { m_Fov = _Fov; }
		void inline SetNearZ(float _NearZ) { m_NearZ = _NearZ; }
		void inline SetFarZ(float _FarZ) { m_FarZ = _FarZ; }
	private:
		float m_ScreenRato;
		float m_Fov;
		float m_NearZ;
		float m_FarZ;
		float m_left;
		float m_Rotation = 0.0f;


		glm::mat4 m_OrthographicMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		glm::vec3 m_Position;
		glm::vec3 m_LookDir;
		glm::vec3 m_LookUp; 

		void RecalculateViewMatrix();
		
	};
	
}

