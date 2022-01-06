#pragma once

#include "Magnus/Core.h"
namespace Magnus {
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	//这样写的好处是可以通过 | 来直接判断是否包含改策略，不用if
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton    = BIT(4)
	};
	class MAGNUS_API Event
	{
		
	public:
		bool Handled = false;
		Event() {

		};
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	protected:
		
	};

	//为了省事，同时为了能直接用#x生成传入参数的字符串
	#define DEFINE_EVENT_TYPE(x) static EventType GetStaticEventType() {return EventType::##x;}\
	EventType GetEventType() const override {return GetStaticEventType();}\
	const char* GetName() const override {return #x;}

	#define DEFINE_EVEN_CATEGORY(x)  int GetCategoryFlags() const override {\
	return EventCategory::##x;}
	

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
	class EventDispatcher
	{
		template<typename T>
		//定义了一个函数指针
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			//判断这个event的类型是不是和传进来函数指针包含的类型一致
			if (m_Event.GetEventType() == T::GetStaticEventType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;

	};

	

}
