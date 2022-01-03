#pragma once
#include "Event.h"
namespace Magnus {
	class MAGNUS_API MouseButtonEvent : public Event
	{
	public:
		

		DEFINE_EVEN_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

	protected:
		MouseButtonEvent(int _Button) :m_Button(_Button) {
		}
		int m_Button;
	};

	class MAGNUS_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int _Button) : MouseButtonEvent(_Button) {

		}
		DEFINE_EVENT_TYPE(MouseButtonPressed)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

	private:

	};

	class MAGNUS_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int _Button) : MouseButtonEvent(_Button) {

		}
		DEFINE_EVENT_TYPE(MouseButtonReleased)

			std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

	private:

	};

	class MAGNUS_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float _X, float _Y) :m_X(_X), m_Y(_Y) {


		}
		inline float GetX() { return m_X; }
		inline float GetY() { return m_Y; }
		DEFINE_EVENT_TYPE(MouseMoved)
		DEFINE_EVEN_CATEGORY(EventCategoryInput | EventCategoryMouse)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_X << ", " << m_Y;
			return ss.str();
		}

	private:
		float m_X, m_Y;
	};
	class MAGNUS_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		DEFINE_EVENT_TYPE(MouseScrolled)
		DEFINE_EVEN_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffset, m_YOffset;
	};
	


	
}