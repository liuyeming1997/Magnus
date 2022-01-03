#pragma once
#include "Event.h"
namespace Magnus {
	class MAGNUS_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int _Width, unsigned int _Height)
			: m_Height(_Height), m_Width(_Width) {

		}
		inline unsigned int GetHeight() { return m_Height; }
		inline unsigned int GetWidth() { return m_Width; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << " , " << m_Height;
			return ss.str();
		}
		DEFINE_EVENT_TYPE(WindowResize)
		DEFINE_EVEN_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Height, m_Width;
	};

	class MAGNUS_API WindowCloseEvent : public Event 
	{
	public:
		WindowCloseEvent() {}
		DEFINE_EVENT_TYPE(WindowClose)
		DEFINE_EVEN_CATEGORY(EventCategoryApplication)

	private:

	};

	class MAGNUS_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}
		DEFINE_EVENT_TYPE(AppTick)
		DEFINE_EVEN_CATEGORY(EventCategoryApplication)

	private:

	};
	class MAGNUS_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		DEFINE_EVENT_TYPE(AppUpdate)
		DEFINE_EVEN_CATEGORY(EventCategoryApplication)
	};

	class MAGNUS_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		DEFINE_EVENT_TYPE(AppRender)
		DEFINE_EVEN_CATEGORY(EventCategoryApplication)
	};



}