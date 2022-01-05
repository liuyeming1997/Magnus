#pragma once
#include "mgpch.h"
#include "Magnus/Core.h"
#include "Magnus/Events/Event.h"
namespace Magnus {
	struct WindowAttribute
	{
		unsigned int m_Height, m_Width;
		std::string m_Title;

		WindowAttribute(const std::string& _Title = "Magnus Engine", unsigned int _Width = 1280,
			unsigned int _Height = 720) : m_Title(_Title), m_Height(_Height), m_Width(_Width) {

		}
	};

	class MAGNUS_API WindowBasic
	{
	public:
		using  EventCallbackFn = std::function<void(Event&)>;
		virtual ~WindowBasic() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallBack(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enbale) = 0;
		virtual bool IsVSync() const = 0;

		static WindowBasic* Create(const WindowAttribute& att = WindowAttribute());


	};

	
}