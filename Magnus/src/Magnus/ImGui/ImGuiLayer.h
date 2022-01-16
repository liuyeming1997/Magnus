#pragma once

#include "Magnus/Core/Layer.h"
#include "Magnus/Events/MouseEvent.h"	
#include "Magnus/Events/KeyEvent.h"
#include "Magnus/Events/ApplicationEvent.h"

namespace Magnus {

	class MAGNUS_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
		
		

	private:
		float m_Time = 0.0f;
	};

}