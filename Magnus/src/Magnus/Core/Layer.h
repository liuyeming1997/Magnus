#pragma once
#include "Magnus/Core/Core.h"
#include "Magnus/Events/Event.h"
#include "Magnus/Core/Timestep.h"
namespace Magnus {
	class MAGNUS_API Layer 
	{
	public:
		Layer(const char * name = "Layer");
		virtual ~Layer();


		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		
		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		const char* m_DebugName;

	};
}