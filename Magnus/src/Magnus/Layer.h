#pragma once
#include "Magnus/Core.h"
#include "Events/Event.h"
namespace Magnus {
	class MAGNUS_API Layer 
	{
	public:
		Layer(const char * name = "Layer");
		virtual ~Layer();


		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		
		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		const char* m_DebugName;

	};
}