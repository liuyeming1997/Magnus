#pragma once
#include "Event.h"

namespace Magnus {
	class KeyEvent : public  Event
	{
	public:
		DEFINE_EVEN_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
			inline int GetKeyCode() const { return m_KeyCode; }
	protected:
		KeyEvent(int _keyCode) :m_KeyCode(_keyCode) {

		}
		int m_KeyCode;

	};
	class  KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		DEFINE_EVENT_TYPE(KeyTyped)
	};

	class KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(int _KeyCode, int _Repeat) : KeyEvent(_KeyCode), m_Repeat(_Repeat) {
			
		}
		DEFINE_EVENT_TYPE(KeyPressed)
		inline int GetRepeatCount() {
			return m_Repeat;
		}
		
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_Repeat << " repeats)";
			return ss.str();
		}

	private:
		int m_Repeat;

	};
	class KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(int _KeyCode) :KeyEvent(_KeyCode) {

		}
		DEFINE_EVENT_TYPE(KeyReleased)
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode ;
			return ss.str();
		}

	};

	



	
	
}